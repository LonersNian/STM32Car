/* Includes ------------------------------------------------------------------*/
#include "motor.h"

/* USER CODE BEGIN 0 */

/****************************小功能函数，用于测试单一电机****************************************/
/*
* brief:下面四个函数电机均反转
*/
void R2_Rotation(void)
{
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET);	//PD6置1
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);	//PD7置0

}

void R1_Rotation(void)
{
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET);	//PC4置1
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET);	//PC5置0

}
void L2_Rotation(void)
{
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);	//PC2置1
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);	//PC3置0

}
void L1_Rotation(void)
{
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);	//PC0置1
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);	//PC1置0

}


/************************************功能函数*****************************************/

//停止
void Stop(void)
{
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);	
}

//前进
void Turnfoward(void)
{
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);	
}

//后退
void Turnback(void)
{
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
}

//左转,原地转圈
void Turnleft(void)
{
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_SET);
	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
}

//右转,原地转圈
void Turnright(void)
{
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET);
    
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);	
   
}
/* USER CODE END 0 */
