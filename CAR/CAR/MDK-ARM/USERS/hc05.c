#include "hc05.h"
#include "stm32f4xx_hal.h"
#include "sys.h"
#include "gpio.h"
#include "motor.h"
#include "time.h"
#include "usart.h"
//全局变量前加g,静态变亮前加s

/**
* 蓝牙控制命令（command判定值）
* 以下宏不放在头文件中，不对外调用
* 
*/
#define CONTROL_STOP         0x00   //停止
#define CONTROL_FRONT        0x01   //前进
#define CONTROL_BACK         0x02   //后退
#define CONTROL_LEFT         0x03   //向左
#define CONTROL_RIGHT        0x04   //向右
#define CONTROL_FAST         0x05   //加速
#define CONTROL_SLOW         0x06   //减速

void Change_CH1_Speed(int num);
void Change_CH2_Speed(int num);
void Change_CH3_Speed(int num);
void Change_CH4_Speed(int num);
void Change_Speed(int num);

void Bluetooth_control(void)    
{
    u16 command;
    u8 aa;
    if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))  //接收中断
	{
        //__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_RXNE);
        
        //HAL_UART_Receive(&huart2,&command,1,1000);
        command = (u16)huart2.Instance->DR;     //查看串口输入值
        switch(command)
          {
            case CONTROL_STOP:      
                Stop();             //停止
                break;
            case CONTROL_FRONT:      
                Turnfoward();       //前进
                break;
            case CONTROL_BACK:      
                Turnback();         //后退
                break;
            case CONTROL_LEFT:      
                Turnleft();         //左转
                break;
            case CONTROL_RIGHT:      
                Turnright();        //右转
                break;
            
            case CONTROL_FAST:      
                 Change_Speed(500); //加速                
                break;
            case CONTROL_SLOW:      
                 Change_Speed(-500); //减速
                break;
          }
	}

}

/**  ==============================================================================
                                    调速函数
    ==============================================================================  **/

/**
* brief:同时调节四个车轮转速
* attention:None
* param:num:占空比变化量
*/
void Change_Speed(int num)
{
    Change_CH1_Speed(num);
    Change_CH2_Speed(num);
    Change_CH3_Speed(num);
    Change_CH4_Speed(num);
}

/**
* brief:通过改变定时器2（对应电机驱动pwm）pwmCH1占空比实现调速
* attention:None
* param:num:占空比变化量
*/
void Change_CH1_Speed(int num)
{
    u8 compare=TIM3->CCR1;
    if(compare==5000)  //满占空比直接返回
    {
        if(num<0) TIM3->CCR1 += num;    //满占空比，只减小
        else return ;
    }
    else if(compare==0)
    {
        if(num>0) TIM3->CCR1 += num;    //零占空比，只增加
        else return ;
    }
    else
    {
    TIM3->CCR1 += num;  //占空比增加200
    }
}

/**
* brief:通过改变定时器2（对应电机驱动pwm）pwmCH1占空比实现调速
* attention:None
* param:num:占空比变化量
*/
void Change_CH2_Speed(int num)
{
    u32 compare=TIM3->CCR2;
    if(compare==5000)  //满占空比直接返回
    {
        if(num<0) TIM3->CCR2 += num;    //满占空比，只减小
        else return ;
    }
    else if(compare==0)
    {
        if(num>0) TIM3->CCR2 += num;    //零占空比，只增加
        else return ;
    }
    else
    {
    TIM3->CCR2 += num;  //占空比增加200
    }
}

/**
* brief:通过改变定时器3（对应电机驱动pwm）pwmCH3占空比实现调速
* attention:None
* param:num:占空比变化量
*/
void Change_CH3_Speed(int num)
{
    u32 compare=TIM3->CCR3;
    if(compare==5000)  //满占空比直接返回
    {
        if(num<0) TIM3->CCR3 += num;    //满占空比，只减小
        else return ;
    }
    else if(compare==0)
    {
        if(num>0) TIM3->CCR3 += num;    //零占空比，只增加
        else return ;
    }
    else
    {
    TIM3->CCR3 += num;  //占空比增加200
    }
}

/**
* brief:通过改变定时器4（对应电机驱动pwm）pwmCH4占空比实现调速
* attention:None
* param:num:占空比变化量
*/
void Change_CH4_Speed(int num)
{
    u32 compare=TIM3->CCR4;
    if(compare==5000)  //满占空比直接返回
    {
        if(num<0) TIM3->CCR4 += num;    //满占空比，只减小
        else return ;
    }
    else if(compare==0)
    {
        if(num>0) TIM3->CCR4 += num;    //零占空比，只增加
        else return ;
    }
    else
    {
    TIM3->CCR4 += num;  //占空比增加200
    }
}
