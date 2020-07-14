#ifndef __TRACK_H
#define __TRACK_H
#include "delay.h"

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 HC05_RX_STA=0;       //接收状态标记	
void Bluetooth_control(void);

#endif /* __TRACK_H */
