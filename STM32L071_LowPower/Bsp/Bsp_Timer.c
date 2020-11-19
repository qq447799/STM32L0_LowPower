#include "Bsp_Timer.h"


//===============================================================
//@�������ƣ�TIM6_Init
//@�������ܣ���ʼ����ʱ��6
//@��ڲ�����  ��
//@���ڲ����������޷���ֵ
//@�� ע	: ��ʱ��6���ڲ��������жϣ�����ϵͳʱ��
//===============================================================
void TIM6_Init_SysMs(void)
{
	TIM_HandleTypeDef htim6;
	
	//ʹ��ʱ��
	__HAL_RCC_TIM6_CLK_ENABLE();
	
	//�ȶԶ�ʱ������Ĭ�ϳ�ʼ��
//	HAL_TIM_Base_DeInit(&htim6);
	
	//���ö�ʱ��
	htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	htim6.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim6.Init.Period = 1000 - 1;
	htim6.Init.Prescaler = 12 - 1;
	htim6.Instance = TIM6;  
	
	//��ʱ����ʼ��
	HAL_TIM_Base_Init(&htim6);

	//������ʱ��
	//HAL_TIM_Base_Start(&htim6);
	
	//�����ж����ȼ�
	HAL_NVIC_SetPriority(TIM6_IRQn,1,2);
	
	//������ʱ���ж�
  HAL_TIM_Base_Start_IT(&htim6);
	
	//ʹ��NVIC�ж�
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
	//ʹ��ʱ��
	__HAL_RCC_LPTIM1_CLK_ENABLE();
	
	RCC->CCIPR = 0x01 << 18;
	
	//���ö�ʱ��
	lptim.Instance = LPTIM1;
		
	lptim.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
	lptim.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV4;
	lptim.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
	lptim.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
	lptim.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
	lptim.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
	

	//��ʱ����ʼ��
	HAL_LPTIM_Init(&lptim);

//	//�����ж����ȼ�
//	HAL_NVIC_SetPriority(LPTIM1_IRQn,1,1);
//	
//	//ʹ��NVIC�ж�
//	HAL_NVIC_EnableIRQ(LPTIM1_IRQn);
	
	/******************NVIC����***************************/
	
		//�����ж����ȼ�
	HAL_NVIC_SetPriority(LPTIM1_IRQn,1,1);
	
/*****************�ⲿ�ж�����***********************/
	Exti_Init.LineCommand = ENABLE;
	Exti_Init.Line_0_31 = LL_EXTI_LINE_29;
	Exti_Init.Mode = LL_EXTI_MODE_IT;
	Exti_Init.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;
	
	LL_EXTI_DeInit();
	LL_EXTI_Init(&Exti_Init);

	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_29);//);	
	//LL_EXTI_GenerateSWI_0_31(IT_1_A_EXTI_LINE);//);
	//ʹ��NVIC�ж�
	HAL_NVIC_EnableIRQ(LPTIM1_IRQn);//);
	
	HAL_LPTIM_TimeOut_Start_IT(&lptim, 0, 37000);
}
