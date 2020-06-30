#include "servo.h"
#include "sys.h"
void Set_compare(u8 compare);
/*
*   ����Ŀ���һ����Ҫһ��20ms���ҵ�ʱ������
*     0.5ms-----------  0��
      1.0ms----------- 45��
      1.5ms----------- 90��
      2.0ms-----------135��
      2.5ms-----------180��
    ���Ҫ��Ϊ��ȷ�Ŀ��ƶ����ת���ǶȲ�<=1�ȣ�������Ҫ�������PWM�źŵ�ռ�ձȣ�
    ���磺�ҿ��԰�0~180��Ϊ1024�ݣ�������ȡ�������붨ʱ����ʱ��Ƶ�ʣ���
    ��ΧΪ0.5ms~2.5ms
    ����Եõ�0.09��/us��
    ��˿����� PWM=0.5+N*0.09��N�ǽǶȣ����ƶ��ת��0~180�ȼ������Ƕȡ�*/
void Servo_control(void)
{
    float angle;
    angle = 100;
    Set_compare(angle);
    
}
void Set_compare(u8 compare)
{
    TIM9->CCR1 = compare;
}