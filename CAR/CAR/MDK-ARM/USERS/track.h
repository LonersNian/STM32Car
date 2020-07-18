#ifndef __TRACK_H
#define __TRACK_H

//在TIM2初始化中加入： HAL_TIM_Base_Start_IT(&htim2);

/***************调用方法，主函数中加入*************/////
 //while (1)
//  {
//  /* USER CODE END WHILE */
//Track_explore();   //红外避障模块检测障碍物
// Track_control();   //循迹控制函数
//  /* USER CODE BEGIN 3 */

//  }
//  /* USER CODE END 3 */


/* Includes ------------------------------------------------------------------*/
void Track_explore(void);   //红外避障模块检测障碍物
void Track_control(void);   //循迹控制函数
void Not_Find_Black(void);

#endif /* __TRACK_H */
