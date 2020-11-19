#ifndef _BSP_TIMER_H_
#define _BSP_TIMER_H_

#include "include.h"

#define CNT_ENABLE			0x01ul

	
void TIM6_Init_SysMs(void);
void TIM6_Start(void);
void TIM6_End(void);

void LP_TIM_Init(void);
#endif


