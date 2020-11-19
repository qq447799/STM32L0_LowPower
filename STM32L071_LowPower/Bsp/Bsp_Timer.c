#include "Bsp_Timer.h"


//===============================================================
//@函数名称：TIM6_Init
//@函数功能：初始化定时器6
//@入口参数：  无
//@出口参数：函数无返回值
//@备 注	: 定时器6用于产生毫秒中断，更新系统时间
//===============================================================
void TIM6_Init_SysMs(void)
{
	TIM_HandleTypeDef htim6;
	
	//使能时钟
	__HAL_RCC_TIM6_CLK_ENABLE();
	
	//先对定时器进行默认初始化
//	HAL_TIM_Base_DeInit(&htim6);
	
	//配置定时器
	htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	htim6.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim6.Init.Period = 1000 - 1;
	htim6.Init.Prescaler = 12 - 1;
	htim6.Instance = TIM6;  
	
	//定时器初始化
	HAL_TIM_Base_Init(&htim6);

	//启动定时器
	//HAL_TIM_Base_Start(&htim6);
	
	//设置中断优先级
	HAL_NVIC_SetPriority(TIM6_IRQn,1,2);
	
	//启动定时器中断
  HAL_TIM_Base_Start_IT(&htim6);
	
	//使能NVIC中断
	HAL_NVIC_EnableIRQ(TIM6_IRQn);
	TIM6_End();
}

void TIM6_Start(void)
{
	TIM6->CNT = 0;
	TIM6->CR1 |= CNT_ENABLE; 

}
void TIM6_End(void)
{
	TIM6->CR1 &= ~CNT_ENABLE; 
}

void LP_TIM_Init(void)
{
	RCC_OscInitTypeDef RCC_osc = {0};
	LPTIM_HandleTypeDef lptim = {0};
	LL_EXTI_InitTypeDef Exti_Init = {0};
		
  RCC_osc.OscillatorType = RCC_OSCILLATORTYPE_LSI;
	RCC_osc.LSIState = RCC_LSI_ON;
	RCC_osc.PLL.PLLState = RCC_PLL_NONE;

	HAL_RCC_OscConfig(&RCC_osc);
	
//	LL_LPTIM_DeInit(LPTIM1);
	HAL_LPTIM_DeInit(&lptim);
	//使能时钟
	__HAL_RCC_LPTIM1_CLK_ENABLE();
	
	RCC->CCIPR = 0x01 << 18;
	
	//配置定时器
	lptim.Instance = LPTIM1;
		
	lptim.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
	lptim.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV4;
	lptim.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
	lptim.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
	lptim.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
	lptim.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
	

	//定时器初始化
	HAL_LPTIM_Init(&lptim);

//	//设置中断优先级
//	HAL_NVIC_SetPriority(LPTIM1_IRQn,1,1);
//	
//	//使能NVIC中断
//	HAL_NVIC_EnableIRQ(LPTIM1_IRQn);
	
	/******************NVIC设置***************************/
	
		//设置中断优先级
	HAL_NVIC_SetPriority(LPTIM1_IRQn,1,1);
	
/*****************外部中断配置***********************/
	Exti_Init.LineCommand = ENABLE;
	Exti_Init.Line_0_31 = LL_EXTI_LINE_29;
	Exti_Init.Mode = LL_EXTI_MODE_IT;
	Exti_Init.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;
	
	LL_EXTI_DeInit();
	LL_EXTI_Init(&Exti_Init);

	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_29);//);	
	//LL_EXTI_GenerateSWI_0_31(IT_1_A_EXTI_LINE);//);
	//使能NVIC中断
	HAL_NVIC_EnableIRQ(LPTIM1_IRQn);//);
	
	HAL_LPTIM_TimeOut_Start_IT(&lptim, 0, 37000);
}
