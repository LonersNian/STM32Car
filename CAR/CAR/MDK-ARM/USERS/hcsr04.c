#include "hcsr04.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "tim.h"
#include "gpio.h"
#include "time.h"
#include "delay.h"
#include "z_usart.h"

u8  TIM14CH1_CAPTURE_STA=0;							//���벶��״̬		    				
u16	TIM14CH1_CAPTURE_VAL; 
//HAL_TIM_IC_Start_IT(&htim14,TIM_CHANNEL_2);   //����TIM2�Ĳ���ͨ��2�����ҿ��������ж�
//__HAL_TIM_ENABLE_IT(&htim14,TIM_IT_UPDATE);   //ʹ�ܸ����ж�
//PA6
//#define TRIG_Pin GPIO_PIN_6
//#define TRIG_GPIO_Port GPIOA
////PA7
//#define ECHO_Pin GPIO_PIN_7
//#define ECHO_GPIO_Port GPIOA

//trig�������ŷ���10us���ϸߵ�ƽ��
//(Echo��>�����ź����)�����ظߵ�ƽ,
//�ߵ�ƽ�ǳ���ʱ���ǳ��������䵽���ص�ʱ��
//����distance=�ߵ�ƽ��ʱ��time*���٣�340m/s��/2 (����)
//һ���ߵ�ƽʱ����Բ��� 0.065536*340=22.28224m(������)
void Hcsr04_Measure()
{
    long long time = 0;     //�õ�
    float distance = 0;     //ʵ�ʾ���
    while(1)
    {
        Hcsr04_Start();
        if(TIM14CH1_CAPTURE_STA&0X80) //�ɹ�������һ�θߵ�ƽ
        {
            time = TIM14CH1_CAPTURE_STA&0X3F;       //�õ��������
            time *= 65535;                          //���ʱ���ܺͣ�����*ÿ��ʱ�䣨��λus����
            time += TIM14CH1_CAPTURE_VAL;           //�õ��ܵĸߵ�ƽʱ��(�����+δ���)
            printf("TIME:%lld us\r\n",time);        //��ӡ�ܵĸߵ�ƽʱ��
            distance = time * 340 * 0.000001;       //TIM14���ù��������1us����λת��
            printf("DISTANCE:%f us\r\n",distance);  //��ӡ�ܵĸߵ�ƽʱ��
            TIM14CH1_CAPTURE_STA=0;                 //������һ�β���
        }
    }
} 

// TRIG������࣬������10us�ĸߵ�ƽ�ź�
void Hcsr04_Start(void)
{
    HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_SET);
    delay_ms(20);
    HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_RESET);
}

//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���
//��ʱ������ж�
void Tim14_High_Level(void)
{
  /* TIM Update event */
    if(__HAL_TIM_GET_FLAG(&htim14, TIM_FLAG_UPDATE) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(&htim14, TIM_IT_UPDATE) !=RESET)
        {
            __HAL_TIM_CLEAR_IT(&htim14, TIM_IT_UPDATE);
            if((TIM14CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
            {
                if(TIM14CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
                    {
                    if((TIM14CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
                        {
                            TIM14CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
                            TIM14CH1_CAPTURE_VAL=65535;
                        }else TIM14CH1_CAPTURE_STA++;
                    }	 
            }
        }
    }
}


//��ʱ�����벶���жϴ���ص��������ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{
	if((TIM14CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
	{
		if(TIM14CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM14CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
                TIM14CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim14,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
                TIM_RESET_CAPTUREPOLARITY(&htim14,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
                TIM_SET_CAPTUREPOLARITY(&htim14,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//����TIM5ͨ��1�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM14CH1_CAPTURE_STA=0;			//���
				TIM14CH1_CAPTURE_VAL=0;
				TIM14CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				__HAL_TIM_DISABLE(&htim14);        //�رն�ʱ��5
				__HAL_TIM_SET_COUNTER(&htim14,0);
				TIM_RESET_CAPTUREPOLARITY(&htim14,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
				TIM_SET_CAPTUREPOLARITY(&htim14,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��5ͨ��1����Ϊ�½��ز���
				__HAL_TIM_ENABLE(&htim14);//ʹ�ܶ�ʱ��5
			}		    
	}	
}

  
  
/*
*  ECHO���һ���ߵ�ƽ���ߵ�ƽ������ʱ����ǳ������ӷ��䵽���ص�ʱ�䡣
*  ���Ծ���=(�ߵ�ƽʱ��*����(340M/S))/2
*/
//void Hcsr04_Measure()
//{
//    TIM_HandleTypeDef htim14;
//    while(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin) == 1)
//        ;
//    Hcsr04_Start();
//	while(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin) == 0)
//        ;                               //�ȴ�echo�ĸߵ�ƽ����	
//    TIM14->CNT &= 0X0000;        //��ռ�����
//    
////	TIM_Cmd(TIM2, ENABLE);  //ʹ�ܶ�ʱ��2,��ʼ����
////	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == 1);//�ȴ�echo�ĸߵ�ƽ����
////    TIM_Cmd(TIM52, DISABLE);	//ʧ�ܶ�ʱ��2,��ֹ����	
////	return (TIM_GetCounter(TIM2))/1000000*340/2 *100;	//�˴���λת��Ϊcm

//}
