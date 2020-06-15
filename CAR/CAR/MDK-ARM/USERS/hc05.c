#include "hc05.h"

void Bluetooth_control(void)    
{
    u8 command;
    if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))  //接收中断
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
////    if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))  //接收中断
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
//    u8  USART2_RX_BUF[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
//    u16 USART2_RX_STA;         		//接收状态标记	
//void Bluetooth_control(void)    
//{

//    if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//	{
//        HAL_UART_Receive(&huart2,&command,1,1000); 
//		if((USART2_RX_STA&0x8000)==0)//接收未完成
//		{
//			if(USART2_RX_STA&0x4000)//接收到了0x0d
//			{
//				if(command!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
//				else USART2_RX_STA|=0x8000;	//接收完成了 
//			}
//			else //还没收到0X0D
//			{	
//				if(command==0x0d)USART2_RX_STA|=0x4000;
//				else
//				{
//					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=command ;
//					USART2_RX_STA++;
//					if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
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
//			len=USART2_RX_STA&0x3fff;//得到此次接收到的数据长度
//			printf("\r\n您发送的消息为:\r\n");
//			HAL_UART_Transmit(&huart2,(uint8_t*)USART2_RX_BUF,len,1000);	//发送接收到的数据
//			while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC)!=SET);		//等待发送结束
//			printf("\r\n\r\n");//插入换行
//			USART2_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nALIENTEK 探索者STM32F407开发板 串口实验\r\n");
//				printf("正点原子@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
//			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
//			delay_ms(10);   
//		} 
//    }	


