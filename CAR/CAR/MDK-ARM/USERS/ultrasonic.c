#include "ultrasonic.h"
#include "tim.h"
#include "gpio.h"
#include "delay.h"
#include "sys.h"
#include "my_delay.h"
#include "sys.h"
#include "servo.h"
#include "motor.h"

#define SOUNDSPEED 340      //声速340m/s
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
		
//下面代码容易跑飞，变成死循环
//触发一个10us的高电平启动超声波
//        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
//        My_delay_us(100);
//        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);       
//        while(HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin) == RESET)        //未接受到高电平
//			
//            ;      
        if(HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin)==SET)                    //已经接受到高电平//接受到回声
        {             
            TIM6->CNT = 0;
            __HAL_TIM_ENABLE(&htim6); //开始计时
            
            while (HAL_GPIO_ReadPin(ECHO2_GPIO_Port, ECHO2_Pin) == SET)       //高电平
                ;          
            __HAL_TIM_DISABLE(&htim6); //结束计时
            temp[i] = (TIM6->CNT)*1e-6; //将单位由us转换为s	
        }
		time+=temp[i];
		delay_ms(10);
    }
    time=(float)time/(5.0);
	distance = ( 100 * time * SOUNDSPEED / 2);
    return distance;  //返回距离 单位cm	
}

//舵机控制角度
#define 	RIGHT  				0			//右
#define 	RIGHT_FRONT			45			//右前
#define 	FRONT	 			90			//前
#define 	LEFT_FRONT			45			//左前
#define 	LEFT 				180			//左

#define 	BLOCK_DISTANCE  	20			//障碍距离，单位m

#define		No_Block                7	// 未发现障碍     111
#define		Middle_Block		    5	// 中间发现障碍   101
#define		Left_Block			    6	// 左边发现障碍   110
#define		Left_Middle_Block   	4	// 左中侧发现障碍 100
#define		Right_Block             3	// 右边发现障碍   011 
#define		Right_Middle_Block      1	// 右中侧发现障碍 001
#define		Left_Right_Block		2	// 左右测发现障碍 010
#define		All_Block               0	// 全部发现障碍   000

/**
* 舵机转动获取不同方向障碍物的距离
* param: direction,超声波朝向
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
	tick = (flag[2]<<2) + (flag[1]<<1) + flag[0];		//转换成二进制方便看
	return tick;
}
/**
* 舵机角度对应超声波方向：0->向右，90->向前，180->向左 
*/
void Ultrasonic_Eluge(void)
{
	
	int tick = Get_Tick();
	switch(tick)
	  {
		case No_Block:      //没有障碍
			Turnfoward();   //前进
			break;
		case Middle_Block:  //中间或全部发现障碍
		case All_Block:
		case Left_Right_Block: //两侧发现障碍，常用于拐角
			Turnback();     //先后退
			delay_ms(500);
		
			Turnleft();     //再左转
			delay_ms(500);
			break;
		case Right_Block:   // 右边发现障碍    
		case Right_Middle_Block:
			Turnleft();     //左转
			break;
		case Left_Block:    // 左边发现障碍    
		case Left_Middle_Block:
			Turnright();    //右转
			break;
		default:            //其他情况
			Turnfoward();   //前进
	  }
	  Angle_control(FRONT);
	  My_delay_ms(1000);
}
	
//	if(front_distance < BLOCK_DISTANCE)
//	{
//		Turnback();   //前进
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


