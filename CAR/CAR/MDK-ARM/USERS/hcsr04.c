#include "hcsr04.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "tim.h"
#include "gpio.h"
#include "time.h"
#include "delay.h"
#include "z_usart.h"

u8  TIM14CH1_CAPTURE_STA=0;							//输入捕获状态		    				
u16	TIM14CH1_CAPTURE_VAL; 
//HAL_TIM_IC_Start_IT(&htim14,TIM_CHANNEL_2);   //开启TIM2的捕获通道2，并且开启捕获中断
//__HAL_TIM_ENABLE_IT(&htim14,TIM_IT_UPDATE);   //使能更新中断
//PA6
//#define TRIG_Pin GPIO_PIN_6
//#define TRIG_GPIO_Port GPIOA
////PA7
//#define ECHO_Pin GPIO_PIN_7
//#define ECHO_GPIO_Port GPIOA

//trig触发引脚发出10us以上高电平后，
//(Echo—>回响信号输出)，返回高电平,
//高电平是持续时间是超声波发射到返回的时间
//距离distance=高电平总时间time*声速（340m/s）/2 (往返)
//一个高电平时间可以测量 0.065536*340=22.28224m(算往返)
void Hcsr04_Measure()
{
    long long time = 0;     //得到
    float distance = 0;     //实际距离
    while(1)
    {
        Hcsr04_Start();
        if(TIM14CH1_CAPTURE_STA&0X80) //成功捕获到了一次高电平
        {
            time = TIM14CH1_CAPTURE_STA&0X3F;       //得到溢出次数
            time *= 65535;                          //溢出时间总和（次数*每次时间（单位us））
            time += TIM14CH1_CAPTURE_VAL;           //得到总的高电平时间(总溢出+未溢出)
            printf("TIME:%lld us\r\n",time);        //打印总的高点平时间
            distance = time * 340 * 0.000001;       //TIM14配置过后计数是1us，单位转换
            printf("DISTANCE:%f us\r\n",distance);  //打印总的高点平时间
            TIM14CH1_CAPTURE_STA=0;                 //开启下一次捕获
        }
    }
} 

// TRIG触发测距，给最少10us的高电平信号
void Hcsr04_Start(void)
{
    HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_SET);
    delay_ms(20);
    HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_RESET);
}

//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数
//定时器溢出中断
void Tim14_High_Level(void)
{
  /* TIM Update event */
    if(__HAL_TIM_GET_FLAG(&htim14, TIM_FLAG_UPDATE) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(&htim14, TIM_IT_UPDATE) !=RESET)
        {
            __HAL_TIM_CLEAR_IT(&htim14, TIM_IT_UPDATE);
            if((TIM14CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
            {
                if(TIM14CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
                    {
                    if((TIM14CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
                        {
                            TIM14CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
                            TIM14CH1_CAPTURE_VAL=65535;
                        }else TIM14CH1_CAPTURE_STA++;
                    }	 
            }
        }
    }
}


//定时器输入捕获中断处理回调函数，该函数在HAL_TIM_IRQHandler中会被调用
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//捕获中断发生时执行
{
	if((TIM14CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
	{
		if(TIM14CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM14CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
                TIM14CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim14,TIM_CHANNEL_1);//获取当前的捕获值.
                TIM_RESET_CAPTUREPOLARITY(&htim14,TIM_CHANNEL_1);   //一定要先清除原来的设置！！
                TIM_SET_CAPTUREPOLARITY(&htim14,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//配置TIM5通道1上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM14CH1_CAPTURE_STA=0;			//清空
				TIM14CH1_CAPTURE_VAL=0;
				TIM14CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				__HAL_TIM_DISABLE(&htim14);        //关闭定时器5
				__HAL_TIM_SET_COUNTER(&htim14,0);
				TIM_RESET_CAPTUREPOLARITY(&htim14,TIM_CHANNEL_1);   //一定要先清除原来的设置！！
				TIM_SET_CAPTUREPOLARITY(&htim14,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//定时器5通道1设置为下降沿捕获
				__HAL_TIM_ENABLE(&htim14);//使能定时器5
			}		    
	}	
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
