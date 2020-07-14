#include "servo.h"
#include "sys.h"
#include "delay.h"
// AS 9P PE5
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
