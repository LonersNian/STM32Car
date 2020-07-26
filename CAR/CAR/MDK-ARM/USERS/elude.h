#ifndef __ELUDE_H
#define __ELUDE_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "motor.h"

// 红外避障情况,不对外调用
//-----------------------------------------------------------------
//#define		No_Block                0x07	// 未发现障碍     111
//#define		Middle_Block		    0x05	// 中间发现障碍   101
//#define		Left_Block			    0x06	// 左边发现障碍   110
//#define		Left_Middle_Block   	0x04	// 左中侧发现障碍 100
//#define		Right_Block        0x03	// 右边发现障碍   011 
//#define		Right_Middle_Block      0x01	// 右中侧发现障碍 001
//#define		Left_Right_Block		0x02	// 左右测发现障碍 010
//#define		All_Block               0x00	// 全部发现障碍   000
//-----------------------------------------------------------------

void Elude_explore(void);   //红外避障模块检测障碍物
void Elude_control(void);   //循迹控制函数
  

#endif /* __ELUDE_H */
