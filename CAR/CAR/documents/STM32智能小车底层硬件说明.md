# STM32智能小车底层硬件说明

标签 ： 底层硬件 

---
##布线要求
###1.涉及到电源：
火线：红线
地线：黑线
电机线：一红一黑，便于区分正反转

电机驱动：
绿线：车轮后转
黄线：前转
**其余布线不用红黑颜色线**

## GPIO引脚对应
###1.板载外设
PE3 KEY1
PE4 KEY0
PA0 WK_UP

PF9 LED0
PF10 LED1

###2.电机驱动
**ps:wh->wheel, L->left, R->right, 1->前轮，2->后轮**
左前电机 WH_L1
PC0 WH_L11 绿
PC1 WH_L12 黄
左后电机 WH_L2
PC2 WH_L21 绿
PC3 WH_L22 黄

右前电机 WH_R1
PC4 WH_R11 绿
PC5 WH_R12 黄
右后电机 WH_R2
PD6 WH_R21 绿
PD7 WH_R22 黄

#### 四路pwm
TIM3_CH1(PC6) ---R2 橙线
TIM3_CH3(PC8) ---R1 棕线

TIM3_CH2(PC7) ---L2 橙线
TIM3_CH4(PC9) ---L1 棕线

#### 蓝牙HC05
PA2 USART2_TX
PA3 USART_RX




