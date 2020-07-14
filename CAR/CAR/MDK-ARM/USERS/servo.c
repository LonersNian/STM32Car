#include "servo.h"
#include "sys.h"
#include "delay.h"
// AS 9P PE5
void Set_compare(int compare);
/*
*   舵机的控制一般需要一个20ms左右的时基脉冲
*     0.5ms-----------  0度      //其实是转到0位置
      1.0ms----------- 45度
      1.5ms----------- 90度
      2.0ms-----------135度
      2.5ms-----------180度
    如果要更为精确的控制舵机（转动角度差<=1度），则需要控制输出PWM信号的占空比，
    例如：我可以把0~180分为1024份（可以任取，决定与定时器的时钟频率），
    范围为0.5ms~2.5ms
    则可以得到0.09度/us，
    因此可以由 PWM=0.5+N*0.09（N是角度）控制舵机转动0~180度间的任意角度。
*/
    u8 dir=1;
    u8 led0pwmval=0;

void Servo_control(void)
{
  
}


/*
* brief: 舵机任意角度控制
* 
* 实现思路：舵机对应TIM9的PWM，挂载在APB2上，时钟频率168M，
*　预分频168-1，计数频率1M，即1us
* 0.5mm占空比为500,2.5mm占空比为2500，中间差了2000，１度对应2000／180＝11.11111.．．，
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
