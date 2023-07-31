/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    user_tools.h
  * @brief   This file contains the headers of useful tools.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
 ******************************************************************************
  */
/* USER CODE END Header */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

/* USER CODE BEGIN EFP */
#ifndef TOOLS_H
#define TOOLS_H
void Delay_100us(uint32_t delay);
float Two_s_Complement_Conversion(uint32_t raw_number, int bit, float mult_factor);
 int   convert_hex2dec            (char *char_input);
 int   convert_gray2dec           (int gray_input);
 char  *dtostrf                   (double val, signed char width, unsigned char prec, char *sout);




#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
