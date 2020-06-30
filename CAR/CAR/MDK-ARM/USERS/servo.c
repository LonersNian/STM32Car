#include "servo.h"
#include "sys.h"
void Set_compare(u8 compare);
/*
*   舵机的控制一般需要一个20ms左右的时基脉冲
*     0.5ms-----------  0度
      1.0ms----------- 45度
      1.5ms----------- 90度
      2.0ms-----------135度
      2.5ms-----------180度
    如果要更为精确的控制舵机（转动角度差<=1度），则需要控制输出PWM信号的占空比，
    例如：我可以把0~180分为1024份（可以任取，决定与定时器的时钟频率），
    范围为0.5ms~2.5ms
    则可以得到0.09度/us，
    因此可以由 PWM=0.5+N*0.09（N是角度）控制舵机转动0~180度间的任意角度。*/
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