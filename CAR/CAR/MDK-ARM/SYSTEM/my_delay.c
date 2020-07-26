#include "my_delay.h"
#include "tim.h"

void My_delay_us(uint16_t time)
{
	uint16_t t1=TIM7->CNT;
	while(TIM7->CNT-t1<time);
}

void My_delay_ms(u16 nms)
{
	u32 i;
	for(i=0;i<nms;i++) My_delay_us(1000);
}
