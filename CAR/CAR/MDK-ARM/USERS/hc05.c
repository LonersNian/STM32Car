#include "hc05.h"
#include "stm32f4xx_hal.h"
#include "sys.h"
#include "gpio.h"
#include "motor.h"
#include "time.h"
#include "usart.h"
//ȫ�ֱ���ǰ��g,��̬����ǰ��s

/**
* �����������command�ж�ֵ��
* ���º겻����ͷ�ļ��У����������
* 
*/
#define CONTROL_STOP         0x00   //ֹͣ
#define CONTROL_FRONT        0x01   //ǰ��
#define CONTROL_BACK         0x02   //����
#define CONTROL_LEFT         0x03   //����
#define CONTROL_RIGHT        0x04   //����
#define CONTROL_FAST         0x05   //����
#define CONTROL_SLOW         0x06   //����

void Change_CH1_Speed(int num);
void Change_CH2_Speed(int num);
void Change_CH3_Speed(int num);
void Change_CH4_Speed(int num);
void Change_Speed(int num);

void Bluetooth_control(void)    
{
    u16 command;
    u8 aa;
    if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))  //�����ж�
	{
        //__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_RXNE);
        
        //HAL_UART_Receive(&huart2,&command,1,1000);
        command = (u16)huart2.Instance->DR;     //�鿴��������ֵ
        switch(command)
          {
            case CONTROL_STOP:      
                Stop();             //ֹͣ
                break;
            case CONTROL_FRONT:      
                Turnfoward();       //ǰ��
                break;
            case CONTROL_BACK:      
                Turnback();         //����
                break;
            case CONTROL_LEFT:      
                Turnleft();         //��ת
                break;
            case CONTROL_RIGHT:      
                Turnright();        //��ת
                break;
            
            case CONTROL_FAST:      
                 Change_Speed(500); //����                
                break;
            case CONTROL_SLOW:      
                 Change_Speed(-500); //����
                break;
          }
	}

}

/**  ==============================================================================
                                    ���ٺ���
    ==============================================================================  **/

/**
* brief:ͬʱ�����ĸ�����ת��
* attention:None
* param:num:ռ�ձȱ仯��
*/
void Change_Speed(int num)
{
    Change_CH1_Speed(num);
    Change_CH2_Speed(num);
    Change_CH3_Speed(num);
    Change_CH4_Speed(num);
}

/**
* brief:ͨ���ı䶨ʱ��2����Ӧ�������pwm��pwmCH1ռ�ձ�ʵ�ֵ���
* attention:None
* param:num:ռ�ձȱ仯��
*/
void Change_CH1_Speed(int num)
{
    u8 compare=TIM3->CCR1;
    if(compare==5000)  //��ռ�ձ�ֱ�ӷ���
    {
        if(num<0) TIM3->CCR1 += num;    //��ռ�ձȣ�ֻ��С
        else return ;
    }
    else if(compare==0)
    {
        if(num>0) TIM3->CCR1 += num;    //��ռ�ձȣ�ֻ����
        else return ;
    }
    else
    {
    TIM3->CCR1 += num;  //ռ�ձ�����200
    }
}

/**
* brief:ͨ���ı䶨ʱ��2����Ӧ�������pwm��pwmCH1ռ�ձ�ʵ�ֵ���
* attention:None
* param:num:ռ�ձȱ仯��
*/
void Change_CH2_Speed(int num)
{
    u32 compare=TIM3->CCR2;
    if(compare==5000)  //��ռ�ձ�ֱ�ӷ���
    {
        if(num<0) TIM3->CCR2 += num;    //��ռ�ձȣ�ֻ��С
        else return ;
    }
    else if(compare==0)
    {
        if(num>0) TIM3->CCR2 += num;    //��ռ�ձȣ�ֻ����
        else return ;
    }
    else
    {
    TIM3->CCR2 += num;  //ռ�ձ�����200
    }
}

/**
* brief:ͨ���ı䶨ʱ��3����Ӧ�������pwm��pwmCH3ռ�ձ�ʵ�ֵ���
* attention:None
* param:num:ռ�ձȱ仯��
*/
void Change_CH3_Speed(int num)
{
    u32 compare=TIM3->CCR3;
    if(compare==5000)  //��ռ�ձ�ֱ�ӷ���
    {
        if(num<0) TIM3->CCR3 += num;    //��ռ�ձȣ�ֻ��С
        else return ;
    }
    else if(compare==0)
    {
        if(num>0) TIM3->CCR3 += num;    //��ռ�ձȣ�ֻ����
        else return ;
    }
    else
    {
    TIM3->CCR3 += num;  //ռ�ձ�����200
    }
}

/**
* brief:ͨ���ı䶨ʱ��4����Ӧ�������pwm��pwmCH4ռ�ձ�ʵ�ֵ���
* attention:None
* param:num:ռ�ձȱ仯��
*/
void Change_CH4_Speed(int num)
{
    u32 compare=TIM3->CCR4;
    if(compare==5000)  //��ռ�ձ�ֱ�ӷ���
    {
        if(num<0) TIM3->CCR4 += num;    //��ռ�ձȣ�ֻ��С
        else return ;
    }
    else if(compare==0)
    {
        if(num>0) TIM3->CCR4 += num;    //��ռ�ձȣ�ֻ����
        else return ;
    }
    else
    {
    TIM3->CCR4 += num;  //ռ�ձ�����200
    }
}
