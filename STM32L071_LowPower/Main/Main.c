#include "Main.h"
#include "Bsp_Gpio.h"

int main(void)
{	
	SystemClock_Config();//配置系统时钟	
	BspInit();//初始化BSP
	TIM6_Start();//毫秒中断，用于更新系统毫秒数
	
	while(1)	
	{
		LED_1_ON;
		delay_ms(500);
		LED_1_OFF;LED_2_ON;
		delay_ms(500);
		LED_2_OFF;LED_3_ON;
		delay_ms(500);
		LED_3_OFF;
		delay_ms(500);
		LED_1_ON;LED_2_ON;LED_3_ON;
		delay_ms(500);
		LED_1_OFF;LED_2_OFF;LED_3_OFF;

		GPIOToLowPowerMode();	//将不用的io口配置为模拟状态，很重要
		__HAL_RCC_PWR_CLK_ENABLE();//使能PWR时钟，很重要，
		
		HAL_PWREx_DisableUltraLowPower();//0: V REFINT is on in low-power mode
		HAL_PWREx_EnableFastWakeUp();//使能快速唤醒
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);//清除唤醒标志

		LP_TIM_Init();
		HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
		
		SystemClock_Config();//配置系统时钟								
		BspInit();//初始化BSP

		TIM6_Start();

	}
}

//===============================================================
//@函数名称：SystemClock_Config
//@函数功能：配置系统时钟
//@入口参数： 
//@出口参数： 无
//@备 注		 ：12MHz
//===================================================================
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;//使用HSI振荡器,16M
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON; 
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;//HSI作为PLL输入源
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3; //PLL3倍频
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_4; //PLL4分频

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;//HCLK为系统时钟1分频
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1; //PCLK1为系统时钟1分频
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;//PCLK2为系统时钟1分频

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}
//===============================================================
//@函数名称：BspInit
//@函数功能：初始化底层硬件
//@入口参数： 
//@出口参数： 无
//@备 注		 ：
//===================================================================
void BspInit(void)
{
	TIM6_Init_SysMs();//毫秒定时器，用于记录相对毫秒
	Bsp_InitLed();
}
void delay_ms(uint16_t ms)
{
	uint16_t i = 0;
	while(ms--)
	{
		i = 0x800;
		while(i--)
			;
	}
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}
