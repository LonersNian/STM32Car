#include "hc05.h"
#define LED0 PFout(9)   	//LED0
#define LED1 PFout(10)   	//LED1
void Bluetooth_control(void)    
{
    u8 command;
    	if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))  //�����ж�
	{
        HAL_UART_Receive(&huart2,&command,1,1000); 
        if(command==123321)
        {
        LED0=!LED0;
        
        }
	 
	}
}
//{
////		if((HC05_RX_STA&0x8000)==0)//����δ���
////		{
////			if(HC05_RX_STA&0x4000)//���յ���0x0d
////			{
////				if(command!=0x0a)HC05_RX_STA=0;//���մ���,���¿�ʼ
////				else HC05_RX_STA|=0x8000;	//��������� 
////			}
////			else //��û�յ�0X0D
////			{	
////				if(command==0x0d)HC05_RX_STA|=0x4000;
////				else
////				{
////					HC05_RX_BUF[HC05_RX_STA&0X3FFF]=command ;
////					HC05_RX_STA++;
////					if(HC05_RX_STA>(HC05_REC_LEN-1))HC05_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
////				}		 
////			}
////		}   	
//}
