#include "servo.h"
#include "sys.h"
#include "delay.h"
// AS 9P PE5
//void MX_TIM9_Init(void)
//{
//  TIM_ClockConfigTypeDef sClockSourceConfig;
//  TIM_OC_InitTypeDef sConfigOC;

//  htim9.Instance = TIM9;
//  htim9.Init.Prescaler = 168 - 1;
//  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim9.Init.Period = 20000;
//  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  HAL_TIM_Base_Init(&htim9);

//  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//  HAL_TIM_ConfigClockSource(&htim9, &sClockSourceConfig);

//  HAL_TIM_PWM_Init(&htim9);

//    
//  sConfigOC.OCMode = TIM_OCMODE_PWM1;
//  sConfigOC.Pulse = 2000;
//  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//  HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
//  HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
//  
//  HAL_TIM_MspPostInit(&htim9);

//}

void Set_compare(int compare);
/*
*   ����Ŀ���һ����Ҫһ��20ms���ҵ�ʱ������
*     0.5ms-----------  0��      //��ʵ��ת��0λ��
      1.0ms----------- 45��
      1.5ms----------- 90��
      2.0ms-----------135��
      2.5ms-----------180��
    ���Ҫ��Ϊ��ȷ�Ŀ��ƶ����ת���ǶȲ�<=1�ȣ�������Ҫ�������PWM�źŵ�ռ�ձȣ�
    ���磺�ҿ��԰�0~180��Ϊ1024�ݣ�������ȡ�������붨ʱ����ʱ��Ƶ�ʣ���
    ��ΧΪ0.5ms~2.5ms
    ����Եõ�0.09��/us��
    ��˿����� PWM=0.5+N*0.09��N�ǽǶȣ����ƶ��ת��0~180�ȼ������Ƕȡ�
*/
    u8 dir=1;
    u8 led0pwmval=0;

void Servo_control(void)
{
  
}


/*
* brief: �������Ƕȿ���
* 
* ʵ��˼·�������ӦTIM9��PWM��������APB2�ϣ�ʱ��Ƶ��168M��
*��Ԥ��Ƶ168-1������Ƶ��1M����1us
* 0.5mmռ�ձ�Ϊ500,2.5mmռ�ձ�Ϊ2500���м����2000�����ȶ�Ӧ2000��180��11.11111.������
*/
void Angle_control(u8 angle)
{
    float unit = 11.11111;
    float temp = 500 + unit * angle;
    int output = (int)(temp);
    Set_compare(output);
}

void Set_compare(int compare)
{
    TIM9->CCR1 = compare;
}
