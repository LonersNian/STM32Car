#include "track.h"

/**
* 循迹功能
* 共三个模块,
    PE2 右
    PE1 中
    PE0 左
* 非黑线,接收到红外光   ：D0引脚低电平->0
* 黑线,未接收到红外光   ：D0引脚高电平->1
*/



u16 Track_Input=0;              //避障模块返回值
u16 Not_Find_Black_flag =0;   //定时器中断时间标志位，用于停车中断
u8  Stop_Flag=0;                 //停车标志位，5s未检测到黑线时为1.

//brief:红外避障模块检测障碍物
void Track_explore(void)
{
    Track_Input=0;
    Track_Input=(((u16)GPIOE->IDR) & 0X07) ;    //取出PE0、1、2三位
}


// 红外循迹情况
//---------------------------------------------------------------------
//#define		Not_Black		    	0x00	// 未发现黑线
//#define		Middle_Black			0x02	// 中间发现黑线
//#define		Left_Black		        0x01	// 左侧发现黑线
//#define		Left_Middle_Black	    0x03	// 左中侧发现黑线
//#define		Right_Black			    0x04	// 右侧发现黑线
//#define		Right_Middle_Black	    0x06	// 右中侧发现黑线
//#define		Left_Right_Black		0x05	// 左右侧发现黑线
//#define		All_Black   			0x07	// 全部发现黑线
//-----------------------------------------------------------------------------------


//    void Stop(void);
//    void Turnfoward(void);
//    void Turnback(void);
//    void Turnleft(void);
//    void Turnright(void);


//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//   if(htim==(&htim2))
//    {
//        LED0=!LED0;        //LED1反转,测试中断用
//    }
//}


/*
* brief:    未发现黑线
*           5s内探测不到黑线，自动停车。
*           tim2配置为1ms,调用5000次
* attention:不能同时和中断回调共用
*/
void Not_Find_Black(void) 
{

 if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE) != RESET)
    {
        if (__HAL_TIM_GET_IT_SOURCE(&htim2, TIM_IT_UPDATE) != RESET)
        {
				__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
	
                Not_Find_Black_flag ++;
            if(Not_Find_Black_flag >= 5000)		// 未发现黑线计时5秒
            {
                Not_Find_Black_flag = 0;
                
                Stop_Flag = 1 ;		// “长时间未发现黑线标志位”置1	
            }
        }
    }    

}
    


//循迹控制函数
void Track_control(void)
{
    if(Track_Input==Not_Black)
    {
        if(Stop_Flag==1)        //5s未发现黑线
        {
            Stop();                  //停止
        }
        else
            Turnfoward();
    }

    else        //发现黑线
    {
        switch(Track_Input)
      {
        Stop_Flag=0;                //只要有黑线标志位就清零
        Not_Find_Black_flag=0;  
          
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
            Turnfoward();         //停止
      }
    }

}
         
