#ifndef __TRACK_H
#define __TRACK_H

//��TIM2��ʼ���м��룺 HAL_TIM_Base_Start_IT(&htim2);

/***************���÷������������м���*************/////
 //while (1)
//  {
//  /* USER CODE END WHILE */
//Track_explore();   //�������ģ�����ϰ���
// Track_control();   //ѭ�����ƺ���
//  /* USER CODE BEGIN 3 */

//  }
//  /* USER CODE END 3 */


/* Includes ------------------------------------------------------------------*/
void Track_explore(void);   //�������ģ�����ϰ���
void Track_control(void);   //ѭ�����ƺ���
void Not_Find_Black(void);

#endif /* __TRACK_H */
