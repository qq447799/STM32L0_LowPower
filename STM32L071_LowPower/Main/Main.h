#ifndef _MAIN_H_
#define _MAIN_H_

#include "include.h"
#include "Bsp_Gpio.h"

void SystemClock_Config(void);
void BspInit(void);
void delay_ms(uint16_t ms);
void Error_Handler(void);
#endif


