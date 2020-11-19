#include "Bsp_LedCtrl.h"
#include "include.h"


//=====================================
//函数名：void Bsp_InitLed(void)
//功能：初始化LED灯
//参数：无
//返回值：无
//=====================================
void Bsp_InitLed(void)
{
	GPIO_InitTypeDef GPIO_Init;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
	
	GPIO_Init.Pin = Bsp_Led1_PIN | Bsp_Led2_PIN | Bsp_Led3_PIN;
	
	HAL_GPIO_Init(Bsp_Led_PORT,&GPIO_Init);
}

