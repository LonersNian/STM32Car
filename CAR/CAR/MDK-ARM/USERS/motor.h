#ifndef __motor_H
#define __motor_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "tim.h"  
#include "gpio.h"     

/* USER CODE BEGIN Includes */
    void R2_Rotation(void);
    void R1_Rotation(void);
    void L1_Rotation(void);
    void L2_Rotation(void);
    void Stop(void);
    void Turnfoward(void);
    void Turnback(void);
    void Turnleft(void);
    void Turnright(void);
/*****************************************************************************/
//下面tim.c文件中CUBEMX不会自动生成,一定要手动添加

///* TIM3 init function */
//void MX_TIM3_Init(void)
//{
//  TIM_ClockConfigTypeDef sClockSourceConfig;
//  TIM_MasterConfigTypeDef sMasterConfig;
//  TIM_OC_InitTypeDef sConfigOC;

//  htim3.Instance = TIM3;
//  htim3.Init.Prescaler = 84-1;
//  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim3.Init.Period = 5000-1;
//  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  HAL_TIM_Base_Init(&htim3);

//  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

//  HAL_TIM_PWM_Init(&htim3);

//  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

//  sConfigOC.OCMode = TIM_OCMODE_PWM1;
//  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

//  
//  主要是下面的不会自动生成
// sConfigOC.Pulse = 1500;
//  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
//  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);

//  sConfigOC.Pulse = 1500;
//  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
// HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);

//  sConfigOC.Pulse = 1500;
//  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3);
// HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);

//  sConfigOC.Pulse = 1500;
//  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4);
//  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);

//  HAL_TIM_MspPostInit(&htim3);

//}

#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */
