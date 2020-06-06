#include "hc05.h"
#define LED0 PFout(9)   	//LED0
#define LED1 PFout(10)   	//LED1
void Bluetooth_control(void)    
{
    u8 command;
    	if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))  //接收中断
	{
        HAL_UART_Receive(&huart2,&command,1,1000); 
        if(command==123321)
        {
        LED0=!LED0;
        
        }
	 
	}
}
//{
////		if((HC05_RX_STA&0x8000)==0)//接收未完成
////		{
////			if(HC05_RX_STA&0x4000)//接收到了0x0d
////			{
////				if(command!=0x0a)HC05_RX_STA=0;//接收错误,重新开始
////				else HC05_RX_STA|=0x8000;	//接收完成了 
////			}
////			else //还没收到0X0D
////			{	
////				if(command==0x0d)HC05_RX_STA|=0x4000;
////				else
////				{
////					HC05_RX_BUF[HC05_RX_STA&0X3FFF]=command ;
////					HC05_RX_STA++;
////					if(HC05_RX_STA>(HC05_REC_LEN-1))HC05_RX_STA=0;//接收数据错误,重新开始接收	  
////				}		 
////			}
////		}   	
//}
