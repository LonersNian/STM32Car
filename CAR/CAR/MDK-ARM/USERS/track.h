#ifndef __TRACK_H
#define __TRACK_H

//在TIM2初始化中加入： HAL_TIM_Base_Start_IT(&htim2);
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "motor.h"

// 红外循迹情况
//---------------------------------------------------------------------
#define		Not_Black		    	0x00	// 未发现黑线
#define		Middle_Black			0x02	// 中间发现黑线
#define		Left_Black		        0x01	// 左侧发现黑线
#define		Left_Middle_Black	    0x03	// 左中侧发现黑线
#define		Right_Black			    0x04	// 右侧发现黑线
#define		Right_Middle_Black	    0x06	// 右中侧发现黑线
#define		Left_Right_Black		0x05	// 左右侧发现黑线
#define		All_Black   			0x07	// 全部发现黑线
//-----------------------------------------------------------------------------------

#define LED0 PFout(9)   	//LED0
#define LED1 PFout(10)   	//LED1
void Track_explore(void);   //红外避障模块检测障碍物
void Track_control(void);   //循迹控制函数
void Not_Find_Black(void);

#endif /* __TRACK_H */
