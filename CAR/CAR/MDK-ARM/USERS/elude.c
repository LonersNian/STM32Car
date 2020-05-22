#include "elude.h"

/**
* 循迹功能
* 共三个模块,
    PD11 左
    PD12 中
    PD13 右
* 有障碍物：out引脚低电平->0
* 无障碍物：out引脚高电平->1
*/


//避障模块返回值
u8 Elude_Input=0;


