/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

#define LED1_On()	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)
#define LED1_Off()	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)
#define LED1_Tgl()	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin)

#define LED2_On()	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET)
#define LED2_Off()	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET)
#define LED2_Tgl()	HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin)

#define LED3_On()	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET)
#define LED3_Off()	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET)
#define LED3_Tgl()	HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin)

#define LED4_On()	HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET)
#define LED4_Off()	HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_RESET)
#define LED4_Tgl()	HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin)

#define LED5_On()	HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_SET)
#define LED5_Off()	HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_RESET)
#define LED5_Tgl()	HAL_GPIO_TogglePin(LED5_GPIO_Port,LED5_Pin)

#define LED6_On()	HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_SET)
#define LED6_Off()	HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_RESET)
#define LED6_Tgl()	HAL_GPIO_TogglePin(LED6_GPIO_Port,LED6_Pin)

#define LED7_On()	HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_SET)
#define LED7_Off()	HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_RESET)
#define LED7_Tgl()	HAL_GPIO_TogglePin(LED7_GPIO_Port,LED7_Pin)

#define BUZZ_On()  HAL_GPIO_WritePin(BUZZ_GPIO_Port,BUZZ_Pin,GPIO_PIN_SET)
#define BUZZ_Off()  HAL_GPIO_WritePin(BUZZ_GPIO_Port,BUZZ_Pin,GPIO_PIN_RESET)
#define BUZZ_Tgl()  HAL_GPIO_TogglePin(BUZZ_GPIO_Port,BUZZ_Pin)

#define is_SWA() HAL_GPIO_ReadPin(SWA_GPIO_Port, SWA_Pin)
#define is_SWB() HAL_GPIO_ReadPin(SWB_GPIO_Port, SWB_Pin)

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
