#include "ultrasonic.h"
#include "tim.h"
#include "gpio.h"
#include "delay.h"
#include "sys.h"
#include "my_delay.h"
#include "sys.h"
#include "servo.h"
#include "motor.h"

#define SOUNDSPEED 340      //����340m/s
#define ECHO2_Pin GPIO_PIN_6
#define ECHO2_GPIO_Port GPIOB

//PA6 TRIG_Pin
//PA7 ECHO_Pin

float UltrasonicDetect(void)
{
    float time = 0;
    int i = 0;
    float temp[5] = {0}; 
		float distance = 0;
		
    for(i=0;i<5;i++)
    {
		do
		{
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
			My_delay_us(100);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);  
		}while(HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin) == RESET);
		
//������������ܷɣ������ѭ��
//����һ��10us�ĸߵ�ƽ����������
//        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
//        My_delay_us(100);
//        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);       
//        while(HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin) == RESET)        //δ���ܵ��ߵ�ƽ
//			
//            ;      
        if(HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin)==SET)                    //�Ѿ����ܵ��ߵ�ƽ//���ܵ�����
        {             
            TIM6->CNT = 0;
            __HAL_TIM_ENABLE(&htim6); //��ʼ��ʱ
            
            while (HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin) == SET)       //�ߵ�ƽ
                ;          
            __HAL_TIM_DISABLE(&htim6); //������ʱ
            temp[i] = (TIM6->CNT)*1e-6; //����λ��usת��Ϊs	
        }
		time+=temp[i];
		delay_ms(10);
    }
    time=(float)time/(5.0);
	distance = ( 100 * time * SOUNDSPEED / 2);
    return distance;  //���ؾ��� ��λcm	
}

//������ƽǶ�
#define 	RIGHT  				0			//��
#define 	RIGHT_FRONT			45			//��ǰ
#define 	FRONT	 			90			//ǰ
#define 	LEFT_FRONT			45			//��ǰ
#define 	LEFT 				180			//��

#define 	BLOCK_DISTANCE  	20			//�ϰ����룬��λm

#define		No_Block                7	// δ�����ϰ�     111
#define		Middle_Block		    5	// �м䷢���ϰ�   101
#define		Left_Block			    6	// ��߷����ϰ�   110
#define		Left_Middle_Block   	4	// ���в෢���ϰ� 100
#define		Right_Block             3	// �ұ߷����ϰ�   011 
#define		Right_Middle_Block      1	// ���в෢���ϰ� 001
#define		Left_Right_Block		2	// ���Ҳⷢ���ϰ� 010
#define		All_Block               0	// ȫ�������ϰ�   000

/**
* ���ת����ȡ��ͬ�����ϰ���ľ���
* param: direction,����������
*/
float Get_Distance(u8 direction)
{
	Angle_control(direction);
	float distance = 0.0;
	My_delay_ms(500);
	distance = UltrasonicDetect();
	return  distance;
}

int Get_Tick(void)
{
	Stop();
	int flag[3] = {0};
	int tick = 0;
	float right_distance = 0.0, left_distance = 0.0, front_distance = 0.0;
	
	front_distance = Get_Distance(FRONT);
	right_distance = Get_Distance(RIGHT);
	left_distance  = Get_Distance(LEFT);
	
	left_distance < BLOCK_DISTANCE ? (flag[0] = 0): (flag[0] = 1);
	front_distance< BLOCK_DISTANCE ? (flag[1] = 0): (flag[1] = 1);
	right_distance< BLOCK_DISTANCE ? (flag[2] = 0): (flag[2] = 1);	
	tick = (flag[2]<<2) + (flag[1]<<1) + flag[0];		//ת���ɶ����Ʒ��㿴
	return tick;
}
/**
* ����Ƕȶ�Ӧ����������0->���ң�90->��ǰ��180->���� 
*/
void Ultrasonic_Eluge(void)
{
	
	int tick = Get_Tick();
	switch(tick)
	  {
		case No_Block:      //û���ϰ�
			Turnfoward();   //ǰ��
			break;
		case Middle_Block:  //�м��ȫ�������ϰ�
		case All_Block:
		case Left_Right_Block: //���෢���ϰ��������ڹս�
			Turnback();     //�Ⱥ���
			delay_ms(500);
		
			Turnleft();     //����ת
			delay_ms(500);
			break;
		case Right_Block:   // �ұ߷����ϰ�    
		case Right_Middle_Block:
			Turnleft();     //��ת
			break;
		case Left_Block:    // ��߷����ϰ�    
		case Left_Middle_Block:
			Turnright();    //��ת
			break;
		default:            //�������
			Turnfoward();   //ǰ��
	  }
	  Angle_control(FRONT);
	  My_delay_ms(1000);
}
	
//	if(front_distance < BLOCK_DISTANCE)
//	{
//		Turnback();   //ǰ��
//		My_delay_ms(500);
//	}
//	else if((left_distance < BLOCK_DISTANCE ) || (right_distance < BLOCK_DISTANCE )) 
//	{
//		Turnback();
//		My_delay_ms(500);
//	}
//	else if((left_distance <= front_distance) && (right_distance <= front_distance))
//	{
//		Turnfoward();
//		My_delay_ms(500);
//	}
//	else if(right_distance <= left_distance)
//	{
//		Turnleft();
//		My_delay_ms(500);
//	}
//	else if(left_distance < right_distance)
//	{
//		Turnright();
//		My_delay_ms(500);
//	}
//	else
//	{
//		Turnfoward();
//	}


