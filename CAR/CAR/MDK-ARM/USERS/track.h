#ifndef __TRACK_H
#define __TRACK_H

//��TIM2��ʼ���м��룺 HAL_TIM_Base_Start_IT(&htim2);
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "motor.h"

// ����ѭ�����
//---------------------------------------------------------------------
#define		Not_Black		    	0x00	// δ���ֺ���
#define		Middle_Black			0x02	// �м䷢�ֺ���
#define		Left_Black		        0x01	// ��෢�ֺ���
#define		Left_Middle_Black	    0x03	// ���в෢�ֺ���
#define		Right_Black			    0x04	// �Ҳ෢�ֺ���
#define		Right_Middle_Black	    0x06	// ���в෢�ֺ���
#define		Left_Right_Black		0x05	// ���Ҳ෢�ֺ���
#define		All_Black   			0x07	// ȫ�����ֺ���
//-----------------------------------------------------------------------------------

#define LED0 PFout(9)   	//LED0
#define LED1 PFout(10)   	//LED1
void Track_explore(void);   //�������ģ�����ϰ���
void Track_control(void);   //ѭ�����ƺ���
void Not_Find_Black(void);

#endif /* __TRACK_H */
