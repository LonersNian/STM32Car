#include "elude.h"

/**
* 避障功能
* 共三个模块,
    PD11 左
    PD12 中
    PD13 右
* 有障碍物,接收到红外光   ：out引脚低电平->0
* 无障碍物,未接收到红外光：out引脚高电平->1
*/


//避障模块返回值
u16 Elude_Input=0;


//brief:红外避障模块检测障碍物
void Elude_explore(void)
{
    Elude_Input=0;
    Elude_Input=(((u16)GPIOD->IDR) & 0X3800)>>11 ;    //取出PD11、12、13三位
}

#define		No_Block                0x07	// 未发现障碍     111
#define		Middle_Block		    0x05	// 中间发现障碍   101
#define		Left_Block			    0x06	// 左边发现障碍   110
#define		Left_Middle_Block   	0x04	// 左中侧发现障碍 100
#define		Right_Block             0x03	// 右边发现障碍   011 
#define		Right_Middle_Block      0x01	// 右中侧发现障碍 001
#define		Left_Right_Block		0x02	// 左右测发现障碍 010
#define		All_Block               0x00	// 全部发现障碍   000

//    void Stop(void);
//    void Turnfoward(void);
//    void Turnback(void);
//    void Turnleft(void);
//    void Turnright(void);

//循迹控制函数
void Elude_control(void)
{
	delay_init(168);               	//初始化延时函数
    switch(Elude_Input)
      {
        case No_Block:      //没有障碍
            Turnfoward();   //前进
            break;
        case Middle_Block:  //中间或全部发现障碍
        case All_Block:
        case Left_Right_Block: //两侧发现障碍，常用于拐角
            Turnback();     //先后退
            delay_ms(500);
        
            Turnleft();     //再左转
            delay_ms(500);

            break;
        case Right_Block:   // 右边发现障碍    
        case Right_Middle_Block:
            Turnleft();     //左转
            break;
        case Left_Block:    // 左边发现障碍    
        case Left_Middle_Block:
            Turnright();    //右转
            break;
        default:            //其他情况
            Turnfoward();   //前进
      }
}
                        
    
    
    
    
