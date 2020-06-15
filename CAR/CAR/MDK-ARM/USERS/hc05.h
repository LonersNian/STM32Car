#ifndef __TRACK_H
#define __TRACK_H

#include "stm32f4xx_hal.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "motor.h"
#include "time.h"
#include "usart.h"


//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 HC05_RX_STA=0;       //����״̬���	
void Bluetooth_control(void);

#endif /* __TRACK_H */
