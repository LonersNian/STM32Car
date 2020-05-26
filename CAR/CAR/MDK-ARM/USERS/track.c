#include "track.h"

/**
* 循迹功能
* 共三个模块,
    PE2 左
    PE1 中
    PE0 右
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


// 红外循迹情况
//---------------------------------------------------------------------
#define		Not_Black		    	0x00	// 未发现黑线
#define		Middle_Black			0x02	// 中间发现黑线
#define		Left_Black		        0x01	// 左侧发现黑线
#define		Left_Middle_Black	    0x03	// 左中侧发现黑线
#define		Right_Black			    0x04	// 右侧发现黑线
#define		Right_Middle_Black	    0x06	// 右中侧发现黑线
#define		Left_Right_Black		0x05	// 左右侧发现黑线
#define		All_Black   			0x07	// 全部发现黑线
//-----------------------------------------------------------------------------------


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
        case Middle_Black:  //中间发现黑线
            Turnfoward();   //前进
            break;
        case Right_Black:   // 右边发现黑线    
        case Right_Middle_Black:
            Turnright();    //右转
            break;
        case Left_Black:    // 左边发现黑线   
        case Left_Middle_Black:
            Turnleft();     //左转
            break;
        default:            //其他情况，比如抬起
            Stop();         //停止
      }
}
                        
    
    
    
    
