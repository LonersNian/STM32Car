#ifndef __TRACK_H
#define __TRACK_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "motor.h"

// ����ѭ�����
//-----------------------------------------------------------------
#define		No_BLACK                0x07	// δ���ֺ���     111
#define		Middle_BLACK		    0x05	// �м䷢�ֺ���   101
#define		Left_BLACK			    0x06	// ��߷��ֺ���   110
#define		Left_Middle_BLACK   	0x04	// ���в෢�ֺ��� 100
#define		Right_BLACK             0x03	// �ұ߷��ֺ���   011 
#define		Right_Middle_BLACK      0x01	// ���в෢�ֺ��� 001
#define		Left_Right_BLACK		0x02	// ���Ҳⷢ�ֺ��� 010

//-----------------------------------------------------------------

void Track_explore(void);   //�������ģ�����ϰ���
void Track_control(void);   //ѭ�����ƺ���
  

#endif /* __TRACK_H */
