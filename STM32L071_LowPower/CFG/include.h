#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef	uint8_t		u8;
typedef	uint16_t	u16;
typedef	uint32_t	u32;	

#include "stm32l0xx_hal_conf.h"		
#include "stm32l0xx_hal_pwr.h"
#include "stm32l0xx_ll_gpio.h"
#include "stm32l0xx_ll_usart.h"
#include "stm32l0xx_ll_lpuart.h"
#include "stm32l0xx_ll_exti.h"

#include "Bsp_LedCtrl.h"
#include "Bsp_Uart.h"
#include "Bsp_Timer.h"

#include "Main.h"
#endif

