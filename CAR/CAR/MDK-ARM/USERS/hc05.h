#ifndef __TRACK_H
#define __TRACK_H

#include "stm32f4xx_hal.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "motor.h"
#include "time.h"
#include "usart.h"

#define HC05_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_HC05_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define RXBUFFERSIZE   1 //�����С
u8 HC05_RX_BUF[HC05_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 HC05_RX_STA=0;       //����״̬���	
void Bluetooth_control(void);

#endif /* __TRACK_H */
