#ifndef _BSP_LEDCTRL_H_
#define _BSP_LEDCTRL_H_

#define Bsp_Led_PORT							GPIOB

#define Bsp_Led1_PIN							GPIO_PIN_7
#define Bsp_Led2_PIN							GPIO_PIN_6
#define Bsp_Led3_PIN							GPIO_PIN_5

#define LED_1_ON 						HAL_GPIO_WritePin(Bsp_Led_PORT, Bsp_Led1_PIN, GPIO_PIN_SET)
#define LED_1_OFF 					HAL_GPIO_WritePin(Bsp_Led_PORT, Bsp_Led1_PIN, GPIO_PIN_RESET)

#define LED_2_ON 						HAL_GPIO_WritePin(Bsp_Led_PORT, Bsp_Led2_PIN, GPIO_PIN_SET)
#define LED_2_OFF 					HAL_GPIO_WritePin(Bsp_Led_PORT, Bsp_Led2_PIN, GPIO_PIN_RESET)

#define LED_3_ON 						HAL_GPIO_WritePin(Bsp_Led_PORT, Bsp_Led3_PIN, GPIO_PIN_SET)
#define LED_3_OFF 					HAL_GPIO_WritePin(Bsp_Led_PORT, Bsp_Led3_PIN, GPIO_PIN_RESET)

void Bsp_InitLed(void);


#endif

