/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    user_spi_interface.h
  * @brief   This file contains the headers of the SPI communication.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_SPI_INTERFACE_H
#define __USER_SPI_INTERFACE_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

#define LOW ((uint8_t)0)
#define HIGH ((uint8_t)1)

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
   
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

/* USER CODE BEGIN EFP */
extern void Set_SSN              (uint8_t level);
extern void Set_SCK_LOW          (void); // does not really works, GPIO is blocked!!
extern void Waiting_For_INTN     (uint32_t timeout); // includes printf() --> OBSOLET, because of using EXTI Interrupt Handling (NVIC)!!
extern void Waiting_For_INTN_UART(char *RX_STR); // size is missing!!

//void Write_Byte(uint8_t *pData1, uint16_t Size1, uint8_t *pData2, uint16_t Size2, uint8_t *byte_array, uint8_t timeout);
//pData1=Opcode, pData2=Address, Array and TimeOut
extern void Set_Bit_No              (uint8_t opcode, uint8_t address, int bit_no);
extern void Write_Opcode            (uint8_t one_byte);
extern void Write_Opcode2           (uint8_t byte1, uint8_t byte2); // used for Measure_Task_Request
extern void Write_Byte              (uint8_t opcode, uint8_t address, uint8_t byte); //not used
extern void Write_Dword             (uint8_t opcode, uint8_t address, uint32_t dword);
extern void Write_Dword_Bits        (uint8_t opcode, uint8_t address, uint8_t msbit, uint8_t lsbit, uint32_t dword);
extern void Update_Dword_Bits       (uint8_t rd_opcode, uint8_t address, uint8_t wr_opcode, uint8_t msbit, uint8_t lsbit, uint32_t dword);
extern void Write_Byte_Auto_Incr    (uint8_t opcode, uint8_t from_addr, uint8_t *byte_array, int to_addr); //not used
extern void Write_Dword_Auto_Incr   (uint8_t opcode, uint8_t from_addr, uint32_t *dword_array, int to_addr);
extern void Write_Register_Auto_Incr(uint8_t opcode, uint8_t from_addr, uint32_t *dword_array, int to_addr);

extern uint32_t Read_Dword     (uint8_t rd_opcode, uint8_t address);
extern uint32_t Read_Dword_Bits(uint8_t rd_opcode, uint8_t address, uint8_t msbit, uint8_t lsbit);

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __USER_SPI_INTERFACE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
