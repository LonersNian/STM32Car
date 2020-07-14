#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "hcsr04.h"
#include "delay.h"
#include "tim.h"

//PA6
#define TRIG_Pin GPIO_PIN_6
#define TRIG_GPIO_Port GPIOA
//PA7
#define ECHO_Pin GPIO_PIN_7
#define ECHO_GPIO_Port GPIOA

// TRIG������࣬������10us�ĸߵ�ƽ�ź�
void Hcsr04_Start(void)
{
    HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_SET);
    delay_us(10);
    HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_RESET);
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