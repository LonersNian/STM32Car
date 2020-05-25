#ifndef __TRACK_H
#define __TRACK_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "motor.h"

// 红外循迹情况
//-----------------------------------------------------------------
#define		No_BLACK                0x07	// 未发现黑线     111
#define		Middle_BLACK		    0x05	// 中间发现黑线   101
#define		Left_BLACK			    0x06	// 左边发现黑线   110
#define		Left_Middle_BLACK   	0x04	// 左中侧发现黑线 100
#define		Right_BLACK             0x03	// 右边发现黑线   011 
#define		Right_Middle_BLACK      0x01	// 右中侧发现黑线 001
#define		Left_Right_BLACK		0x02	// 左右测发现黑线 010

//-----------------------------------------------------------------

void Track_explore(void);   //红外避障模块检测障碍物
void Track_control(void);   //循迹控制函数
  

#endif /* __TRACK_H */
