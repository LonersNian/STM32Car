#ifndef __TRACK_H
#define __TRACK_H

#include "stm32f4xx_hal.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "motor.h"
#include "time.h"
#include "usart.h"

#define HC05_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_HC05_RX 			1		//使能（1）/禁止（0）串口1接收
#define RXBUFFERSIZE   1 //缓存大小
u8 HC05_RX_BUF[HC05_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 HC05_RX_STA=0;       //接收状态标记	
void Bluetooth_control(void);

#endif /* __TRACK_H */
