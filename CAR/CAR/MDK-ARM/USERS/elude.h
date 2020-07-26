#ifndef __ELUDE_H
#define __ELUDE_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "motor.h"

// ����������,���������
//-----------------------------------------------------------------
//#define		No_Block                0x07	// δ�����ϰ�     111
//#define		Middle_Block		    0x05	// �м䷢���ϰ�   101
//#define		Left_Block			    0x06	// ��߷����ϰ�   110
//#define		Left_Middle_Block   	0x04	// ���в෢���ϰ� 100
//#define		Right_Block        0x03	// �ұ߷����ϰ�   011 
//#define		Right_Middle_Block      0x01	// ���в෢���ϰ� 001
//#define		Left_Right_Block		0x02	// ���Ҳⷢ���ϰ� 010
//#define		All_Block               0x00	// ȫ�������ϰ�   000
//-----------------------------------------------------------------

void Elude_explore(void);   //�������ģ�����ϰ���
void Elude_control(void);   //ѭ�����ƺ���
  

#endif /* __ELUDE_H */
