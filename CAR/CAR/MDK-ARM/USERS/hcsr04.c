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

// TRIG触发测距，给最少10us的高电平信号
void Hcsr04_Start(void)
{
    HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_SET);
    delay_us(10);
    HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_RESET);
}

/*
*  ECHO输出一个高电平，高电平持续的时间就是超声波从发射到返回的时间。
*  测试距离=(高电平时间*声速(340M/S))/2
*/
//void Hcsr04_Measure()
//{
//    TIM_HandleTypeDef htim14;
//    while(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin) == 1)
//        ;
//    Hcsr04_Start();
//	while(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin) == 0)
//        ;                               //等待echo的高电平到来	
//    TIM14->CNT &= 0X0000;        //清空计数器
//    
////	TIM_Cmd(TIM2, ENABLE);  //使能定时器2,开始计数
////	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == 1);//等待echo的高电平结束
////    TIM_Cmd(TIM52, DISABLE);	//失能定时器2,截止计数	
////	return (TIM_GetCounter(TIM2))/1000000*340/2 *100;	//此处单位转换为cm

//}