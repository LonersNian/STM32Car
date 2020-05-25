#include "track.h"

/**
* 循迹功能
* 共三个模块,
    PD11 左
    PD12 中
    PD13 右
* 非黑线,接收到红外光   ：D0引脚低电平->0
* 黑线,未接收到红外光   ：D0引脚高电平->1
*/


//避障模块返回值
u16 Track_Input=0;


//brief:红外避障模块检测障碍物
void Track_explore(void)
{
    Track_Input=0;
    Track_Input=(((u16)GPIOD->IDR) & 0X3800)>>11 ;    //取出PD11、12、13三位
}

//// 红外循迹情况
////-----------------------------------------------------------------
//#define		No_BLACK                0x07	// 未发现黑线     111
//#define		Middle_BLACK		    0x05	// 中间发现黑线   101
//#define		Left_BLACK			    0x06	// 左边发现黑线   110
//#define		Left_Middle_BLACK   	0x04	// 左中侧发现黑线 100
//#define		Right_BLACK             0x03	// 右边发现黑线   011 
//#define		Right_Middle_BLACK      0x01	// 右中侧发现黑线 001
//#define		Left_Right_BLACK		0x02	// 左右测发现黑线 010
////-----------------------------------------------------------------


//    void Stop(void);
//    void Turnfoward(void);
//    void Turnback(void);
//    void Turnleft(void);
//    void Turnright(void);

//循迹控制函数
void Track_control(void)
{
	delay_init(168);        //初始化延时函数
    switch(Track_Input)
      {
        case Middle_BLACK:  //中间发现黑线
            Turnfoward();   //前进
            break;
        case Right_BLACK:   // 右边发现黑线    
        case Right_Middle_BLACK:
            Turnright();    //右转
            break;
        case Left_BLACK:    // 左边发现黑线   
        case Left_Middle_BLACK:
            Turnleft();     //左转
            break;
        default:            //其他情况，比如抬起
            Stop();         //停止
      }
}
                        
    
    
    
    
