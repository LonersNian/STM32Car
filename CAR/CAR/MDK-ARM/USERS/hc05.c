#include "hc05.h"

void Bluetooth_control(void)    
{
    u8 command;
    if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))  //�����ж�
	{
        //HAL_UART_Receive(&huart2,&command,1,1000);
        command = (u16)huart2.Instance->DR;
        //command=4;
             //   HAL_UART_Transmit(&huart2,&command,1,1000);
        if(command == 0x38)
        {
        HAL_GPIO_WritePin(GPIOF, LED0_Pin, GPIO_PIN_SET);

        }
        
	 
	}
    huart2.Instance->DR=0x0;
}
//    u8 command;
//    u8 len;	
//	u16 times=0;
////    if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))  //�����ж�
////	{
////        //HAL_UART_Receive(&huart2,&command,1,1000);
////        command = (u16)huart2.Instance->DR;
////        if(command == 12)
////        {
////        LED0=!LED0;
////        
////        }
////	 
////	}
//    u8  USART2_RX_BUF[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
//    u16 USART2_RX_STA;         		//����״̬���	
//void Bluetooth_control(void)    
//{

//    if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//	{
//        HAL_UART_Receive(&huart2,&command,1,1000); 
//		if((USART2_RX_STA&0x8000)==0)//����δ���
//		{
//			if(USART2_RX_STA&0x4000)//���յ���0x0d
//			{
//				if(command!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
//				else USART2_RX_STA|=0x8000;	//��������� 
//			}
//			else //��û�յ�0X0D
//			{	
//				if(command==0x0d)USART2_RX_STA|=0x4000;
//				else
//				{
//					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=command ;
//					USART2_RX_STA++;
//					if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//				}		 
//			}
//		}   		 
//	}
//	HAL_UART_IRQHandler(&huart2);
// 
//    
//}
//void lanya(void)
//{

//  while(1)
//    {
//			
//       if(USART2_RX_STA&0x8000)
//		{					   
//			len=USART2_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
//			printf("\r\n�����͵���ϢΪ:\r\n");
//			HAL_UART_Transmit(&huart2,(uint8_t*)USART2_RX_BUF,len,1000);	//���ͽ��յ�������
//			while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
//			printf("\r\n\r\n");//���뻻��
//			USART2_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nALIENTEK ̽����STM32F407������ ����ʵ��\r\n");
//				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("����������,�Իس�������\r\n");  
//			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
//			delay_ms(10);   
//		} 
//    }	


