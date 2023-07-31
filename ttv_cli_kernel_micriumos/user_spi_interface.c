/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hspi1_interface.c
  * @brief   SPI Interface Communication Routines, including UART.
  *
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    SPI Timings
      SSN enable to valid latch clock = min. 1.7us (2.6us)
      SSN hold time after SCK falling = min. 2.2us (3.6us)

    Timing in between the bytes
      Transmitting incremental = no additional gap           (recommended usage)
      Transmitting bytewise = approx. 3.5us

      Receiving incremental = approx. 1us                    (recommended usage)
      Receiving bytewise = approx. 5us

    Transmitting and Receiving Examples
    //declaration
      uint8_t timeout = 10; //Timeout duration in millisecond [ms]
      uint8_t spiTX[3];
      uint8_t spiRX[3];
      spiTX[0]=0xAA;
      spiTX[1]=0xBB;
      spiTX[2]=0xCC;

    //Example: transmitting bytes without gap in between           (recommended)
      Set_SSN(LOW);
      HAL_SPI_Transmit(&hspi1, spiTX, 3, timeout);
      Set_SSN(HIGH);

    //Example: transmitting bytewise with gap of approx. 3.5us in between
      Set_SSN(LOW);
      HAL_SPI_Transmit(&hspi1, &spiTX[0], 1, timeout);
      HAL_SPI_Transmit(&hspi1, &spiTX[1], 1, timeout);
      HAL_SPI_Transmit(&hspi1, &spiTX[2], 1, timeout);
      Set_SSN(HIGH);

    //Example: receiving bytewise with gap of ~1us in between      (recommended)
      Set_SSN(LOW);
      HAL_SPI_Receive(&hspi1, spiRX, 3, timeout); //gap between read bytes 1us
      Set_SSN(HIGH);

    //Example: receiving bytewise with gap of ~5us in between
      Set_SSN(LOW);
      HAL_SPI_Receive(&hspi1, &spiRX[0], 1, timeout);
      HAL_SPI_Receive(&hspi1, &spiRX[1], 1, timeout);
      HAL_SPI_Receive(&hspi1, &spiRX[2], 1, timeout);
      Set_SSN(HIGH);

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "os.h"
#include "user_spi_interface.h"
#include "cli.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "spidrv.h"
#include "sl_spidrv_instances.h"
#include "sl_uartdrv_instances.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
RTOS_ERR* SPI_ERR;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
#define SPI_HANDLE                  sl_spidrv_exp_handle
#define UART_HANDLE                 sl_uartdrv_usart_exp_handle

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */
void callback(){

  return;
}
/******************************************************************************/
/*                                  Set SSN                                   */
/******************************************************************************/
/**
  * @brief  Set or clear the level of SSN pin
  * @param  level specifies the level to be written to SSN pin
  *            @arg LOW: to clear the SSN pin
  *            @arg HIGH: to set the SSN pin
  * @retval none
  */

void GPIO_init(){

}
void delay(uint32_t dlyTicks)
{

  uint32_t curTicks;

  curTicks = sl_sleeptimer_get_tick_count64();
  while ((sl_sleeptimer_get_tick_count64() - curTicks) < dlyTicks)
  {
    __NOP();
  }
}
void Set_SSN(uint8_t level)
{
  if(level == LOW) {
    GPIO_PinOutClear(gpioPortE,13);
  }
  if(level == HIGH) {
    GPIO_PinOutSet(gpioPortE,13);
  }
}

/******************************************************************************/
/*                               Set SCK to low                               */
/******************************************************************************/
/**
  * @brief  Set the SCK level to low.
  * @retval none
  */
void Set_SCK_LOW(void)
{
  /*to set low SPI_SCK*/
  GPIO_PinOutClear(gpioPortE,12);
}

/******************************************************************************/
/*                   Waiting for interrupt with set timeout                   */
/******************************************************************************/
/**
  * @brief  Waiting for interrupt.
  * @param  Timeout Timeout duration
  * @retval none
  */
void Waiting_For_INTN(uint32_t timeout)
{
  uint32_t tickstart;
  
  /*Init tickstart for timeout management */
  tickstart = sl_sleeptimer_get_tick_count64();

  /*step a - Waiting for the interrupt INTN (low active) */
  while(GPIO_PinInGet(gpioPortA, 12))
  {
    /* Timeout management */
    if ((((sl_sleeptimer_get_tick_count64() - tickstart) >=  timeout) && (timeout != 0xFFFFFFFFU)) || (timeout == 0U))
    {
      printf("TIMEOUT after %u ms\n", (unsigned int)timeout);
    }
  }
}

/******************************************************************************/
/*                                  Set SSN                                   */
/******************************************************************************/
/**
  * @brief  Waiting for interrupt and polling the UART RX.
  * @param  RX_STR pointer to RX buffer
  * @param  size amount of data to be received
  * @retval none
  */
void Waiting_For_INTN_UART(char *RX_STR) //size is missing (15-1)
{
  /* waiting for the interrupt INTN (low active) */
  while(GPIO_PinInGet(gpioPortA, 12)) {
    UARTDRV_Receive ( UART_HANDLE,
                      (uint8_t*)RX_STR,
    15-1,
    callback
    );
    delay(10);
  }
}

/******************************************************************************/
/*                         Set one bit of double word                         */
/******************************************************************************/
/**
  * @brief  Set one bit of double word.
  * @param  opcode (byte)
  * @param  address (byte)
  * @param  bit_no (uint8_t) 31..0
  * @retval none
  */
void Set_Bit_No(uint8_t opcode, uint8_t address, int bit_no)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10;
  uint8_t spiTX[6];
  uint32_t temp_u32 = 1;

  if (bit_no > 31) bit_no = 31;
  if (bit_no < 0) bit_no = 0;
  
  spiTX[0] = opcode;
  spiTX[1] = address;
  temp_u32 <<= bit_no;
  spiTX[2] = temp_u32>>24;
  spiTX[3] = temp_u32>>16;
  spiTX[4] = temp_u32>>8;
  spiTX[5] = temp_u32;
  
  /* 1. Put SSN low - Activate */
  Set_SSN(LOW);
  
  /* 2. Transmit register address */
  SPIDRV_MTransmitB  (SPI_HANDLE,
  spiTX,
  6
  );
  OSTimeDly (timeout,
             OS_OPT_TIME_DLY ,
                   SPI_ERR   );
  /* 3. Put SSN high - Deactivate */
  Set_SSN(HIGH);
}

/******************************************************************************/
/*                            Write one byte Opcode                           */
/******************************************************************************/
/**
  * @brief  Write one byte Opcode.
  * @param  one_byte
  * @retval none
  */
void Write_Opcode(uint8_t one_byte)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10;
  
  /* 1. Put SSN low - Activate */
  //Set_SSN(LOW);
  
  /* 2. Transmit register address */
  SPIDRV_MTransmitB  (SPI_HANDLE,
  &one_byte,
  1
  );
  delay(10);
  
  /* 3. Put SSN high - Deactivate */
 // Set_SSN(HIGH);
}

/******************************************************************************/
/*                               Write two bytes                              */
/******************************************************************************/
/**
  * @brief  Write two bytes.
  * @param  byte1 (e.g. opcode RC_MT_REQ)
  * @param  byte2 (e.g. request EC_MT_REQ_BITx)
  * @retval none
  */
void Write_Opcode2(uint8_t byte1, uint8_t byte2)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10;
  uint8_t spiTX[2];

  spiTX[0] = byte1;
  spiTX[1] = byte2;
      
  /* 1. Put SSN low - Activate */
  Set_SSN(LOW);
  
  /* 2. Transmit register address */
  SPIDRV_MTransmitB  (SPI_HANDLE,
    spiTX,
    2
    );
  delay(10);
  /* 3. Put SSN high - Deactivate */
  Set_SSN(HIGH);
}

/******************************************************************************/
/*                             Write one data byte                            */
/******************************************************************************/
/**
  * @brief  Write one byte.
  * @param  opcode (byte)
  * @param  address (byte)
  * @param  byte (byte)
  * @retval none
  */
void Write_Byte(uint8_t opcode, uint8_t address, uint8_t byte)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10;
  uint8_t spiTX[3];

  spiTX[0] = opcode;
  spiTX[1] = address;
  spiTX[2] = byte;
      
  /* 1. Put SSN low - Activate */
  Set_SSN(LOW);
  
  /* 2. Transmit register address */
  SPIDRV_MTransmitB  (SPI_HANDLE,
    spiTX,
    3
    );
  delay(10);
  /* 3. Put SSN high - Deactivate */
  Set_SSN(HIGH);
}

/******************************************************************************/
/*                         Write one data double word                         */
/******************************************************************************/
/**
  * @brief  Write one double word.
  * @param  opcode (byte)
  * @param  address (byte)
  * @param  dword (double word)
  * @retval none
  */
void Write_Dword(uint8_t opcode, uint8_t address, uint32_t dword)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10;
  uint8_t spiTX[6];
  uint32_t temp_u32 = 0;

  spiTX[0] = opcode;
  spiTX[1] = address;
  temp_u32 = dword;
  spiTX[2] = temp_u32>>24;
  spiTX[3] = temp_u32>>16;
  spiTX[4] = temp_u32>>8;
  spiTX[5] = temp_u32;
      
  /* 1. Put SSN low - Activate */
  Set_SSN(LOW);
  
  /* 2. Transmit register address */
  SPIDRV_MTransmitB  (SPI_HANDLE,
    spiTX,
    6
    );
  delay(10);

  /* 3. Put SSN high - Deactivate */
  Set_SSN(HIGH);
}

/******************************************************************************/
/*                       Write only bits of double word                       */
/******************************************************************************/
/**
  * @brief  This function writes only the specified bits (from msbit to lsbit)
  *             to the address without reading first.
  * @param  opcode (byte)
  * @param  address (byte)
  * @param  msbit (byte) most significat bit
  * @param  lsbit (byte) low significant bit
  * @param  dword (double word)
  * @retval none
  */
void Write_Dword_Bits(uint8_t opcode, uint8_t address, uint8_t msbit, uint8_t lsbit, uint32_t dword)
{
//#define _DEBUGGGING_FUNCTION
  
  uint32_t bit_amount = 0;
  uint32_t bit_mask = 0;
  uint32_t bit_mask_inv = 0xFFFFFFFF;
  uint32_t temp_u32 = 0;
  
  /* out of range [31:0] */
  if (msbit > 31) msbit = 31;
  if (lsbit > 31) lsbit = 31;
  
  if (lsbit > msbit) lsbit = msbit;

  /* build the mask */
  bit_amount = msbit - lsbit;
  for (int i = 0; i < bit_amount + 1; i++) {
    bit_mask <<= 1;
    bit_mask += 1;
  }
  bit_mask <<= lsbit;
  bit_mask_inv -= bit_mask;

  /* Change specified bits at shifted position*/
  temp_u32 = dword << lsbit;
  
  /* within the limits */
  temp_u32 &= bit_mask;

#ifdef _DEBUGGGING_FUNCTION
  /* for debugging */
  puts("Write_Dword_Bits");
  printf(" opcode = 0x%02X\taddress = 0x%02X\n", opcode, address);
  printf(" msb = %u\tlsb = %u\n", msbit, lsbit);
  printf(" value to be written = 0x%08X\n", temp_u32);
  printf(" bit_mask = 0x%08X\tbit_mask_inv = 0x%08X\n", bit_mask, bit_mask_inv);
#endif
  
  /* Write content */
  Write_Dword(opcode, address, temp_u32);

#undef _DEBUGGGING_FUNCTION
}

/******************************************************************************/
/*                       Update only bits of double word                       */
/******************************************************************************/
/**
  * @brief  This function updates the specified bits (from msbit to lsbit) by 
  *             reading the content of address first. After that, the updated 
  *             content will be written.
  * @param  rd_opcode (byte) for reading double word
  * @param  address (byte)
  * @param  wr_opcode (byte) for writing updated double word
  * @param  msbit (byte) most significat bit
  * @param  lsbit (byte) low significant bit
  * @param  dword (double word)
  * @retval none
  */
void Update_Dword_Bits(uint8_t rd_opcode, uint8_t address, uint8_t wr_opcode, uint8_t msbit, uint8_t lsbit, uint32_t dword)
{
//#define _DEBUGGGING_FUNCTION
  
  uint32_t bit_amount = 0;
  uint32_t bit_mask = 0;
  uint32_t bit_mask_inv = 0xFFFFFFFF;
  uint32_t temp_u32 = 0;
  
  uint32_t address_content = 0;
  
  /* out of range [31:0] */
  if (msbit > 31) msbit = 31;
  if (lsbit > 31) lsbit = 31;
  
  if (lsbit > msbit) lsbit = msbit;

  /* build the mask */
  bit_amount = msbit - lsbit;
  for (int i = 0; i < bit_amount + 1; i++) {
    bit_mask <<= 1;
    bit_mask += 1;
  }
  bit_mask <<= lsbit;
  bit_mask_inv -= bit_mask;

  
  /* Read content of address */
  address_content = Read_Dword(rd_opcode, address);
  
  /* Change specified bits at shifted position*/
  temp_u32 = dword << lsbit;

#ifdef _DEBUGGGING_FUNCTION
  /* for debugging */
  puts("Update_Dword_Bits");
  printf(" RD_opcode = 0x%02X\tWR_opcode = 0x%02X\taddress = 0x%02X\n", rd_opcode, wr_opcode, address);
  printf(" msb = %u\tlsb = %u\n", msbit, lsbit);
  printf(" read content = 0x%08X\tvalue to be written = 0x%08X\n", address_content, temp_u32);
  printf(" bit_mask = 0x%08X\tbit_mask_inv = 0x%08X\n", bit_mask, bit_mask_inv);
#endif
  
  /* Clear specified bits of content */
  address_content &= bit_mask_inv;

#ifdef _DEBUGGGING_FUNCTION
  /* for debugging */
  printf(" cleared range = %08X\n", address_content);
#endif
  
  /* Write content */
  address_content |= temp_u32;
  Write_Dword(wr_opcode, address, address_content);

#ifdef _DEBUGGGING_FUNCTION
  /* for debugging */
  printf(" written = %08X\n", address_content); 
#endif
  
#undef _DEBUGGGING_FUNCTION
}

/******************************************************************************/
/*                       Write bytes auto incrementally                       */
/******************************************************************************/
/**
  * @brief  Write bytes incrementally.
  * @param  opcode (byte)
  * @param  from_addr (byte)
  * @param  byte_array
  * @param  to_addr (32 bit)
  * @retval none
  */
void Write_Byte_Auto_Incr(uint8_t opcode, uint8_t from_addr, uint8_t *byte_array, int to_addr)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10;
  uint8_t spiTX[2];
  
  spiTX[0] = opcode;
  spiTX[1] = from_addr;

  /* 1. Put SSN low - Activate */
  Set_SSN(LOW);

  /* 2.a Transmit register address */
  SPIDRV_MTransmitB  (SPI_HANDLE,
      spiTX,
      2
      );
  delay(10);
  /* 2.b Transmit register address incrementally */
  for (int i = from_addr; i <= to_addr; i++) {
    SPIDRV_MTransmitB  (SPI_HANDLE,
        byte_array,
        1
        );
    delay(10);
    
    byte_array++;
  }
  
  /* 3. Put SSN high - Deactivate */
  Set_SSN(HIGH);
}

/******************************************************************************/
/*                    Write double words auto incrementally                   */
/******************************************************************************/
/**
  * @brief  Write double words incrementally.
  * @param  opcode (byte)
  * @param  from_addr (byte)
  * @param  dword_array
  * @param  to_addr (32 bit)
  * @retval none
  */
void Write_Dword_Auto_Incr(uint8_t opcode, uint8_t from_addr, uint32_t *dword_array, int to_addr)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10;
  uint8_t spiTX[4];
  uint32_t temp_u32 = 0;

  spiTX[0] = opcode;
  spiTX[1] = from_addr;

  /* to start at expected index */
  dword_array += from_addr; 
  
  /* 1. Put SSN low - Activate */
  Set_SSN(LOW);

  /* 2.a Transmit register address */
  SPIDRV_MTransmitB  (SPI_HANDLE,
      spiTX,
      2
      );
  delay(10);
  /* 2.b Transmit register address incrementally */
  for (int i = from_addr; i <= to_addr; i++) {
    temp_u32 = *dword_array;
    spiTX[0] = temp_u32>>24;
    spiTX[1] = temp_u32>>16;
    spiTX[2] = temp_u32>>8;
    spiTX[3] = temp_u32;

    SPIDRV_MTransmitB  (SPI_HANDLE,
        spiTX,
        4
        );
    delay(10);
    dword_array++;
  }
  
  /* 3. Put SSN high - Deactivate */
  Set_SSN(HIGH);
}

/******************************************************************************/
/*                      Write register auto incrementally                     */
/******************************************************************************/
/**
  * @brief  Write double words incrementally.
  * @param  opcode (byte)
  * @param  from_addr (byte)
  * @param  dword_array
  * @param  to_addr (32 bit)
  * @retval none
  */
void Write_Register_Auto_Incr(uint8_t opcode, uint8_t from_addr, uint32_t *dword_array, int to_addr)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10;
  uint8_t spiTX[4];
  uint32_t temp_u32 = 0;

  spiTX[0] = opcode;
  spiTX[1] = from_addr;

//  /* to start at expected index */
//  dword_array += from_addr; 
  
  /* 1. Put SSN low - Activate */
  Set_SSN(LOW);

  /* 2.a Transmit register address */
  SPIDRV_MTransmitB  (SPI_HANDLE,
      spiTX,
      2
      );
  delay(10);
  /* 2.b Transmit register address incrementally */
  for (int i = from_addr; i <= to_addr; i++) {
    temp_u32 = *dword_array;
    spiTX[0] = temp_u32>>24;
    spiTX[1] = temp_u32>>16;
    spiTX[2] = temp_u32>>8;
    spiTX[3] = temp_u32;

    SPIDRV_MTransmitB  (SPI_HANDLE,
        spiTX,
        4
        );
    delay(10);
    dword_array++;
  }
  
  /* 3. Put SSN high - Deactivate */
  Set_SSN(HIGH);
}

/******************************************************************************/
/*                              Read double word                              */
/******************************************************************************/
/**
  * @brief  Read double word.
  * @param  opcode (byte)
  * @param  address (byte)
  * @retval 32-bit value
  */
uint32_t Read_Dword(uint8_t rd_opcode, uint8_t address)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10;
  uint8_t spiTX[2];
  uint8_t spiRX[4];
  uint32_t temp_u32 = 0;
  
  spiTX[0] = rd_opcode;
  spiTX[1] = address;
  
  /* 1. Put SSN low - Activate */
  Set_SSN(LOW);
  
  /* 2. Transmit register address */
  SPIDRV_MTransmitB  (SPI_HANDLE,
      spiTX,
      2
      );
  delay(10);
  /*3. Read four bytes */
  SPIDRV_MReceiveB  (SPI_HANDLE,
      spiRX,
      4
      );
  delay(10);
  /* 4. Put SSN high - Deactivate */
  Set_SSN(HIGH);
  
  /*Concatenate of bytes (from MSB to LSB) */
  temp_u32 = (spiRX[0]<<24) + (spiRX[1]<<16) + (spiRX[2]<<8) + (spiRX[3]);
  
  return temp_u32;
}

/******************************************************************************/
/*                              Read double word                              */
/******************************************************************************/
/**
  * @brief  Read double word.
  * @param  opcode (byte) for reading double word
  * @param  address (byte)
  * @param  msbit (byte) most significat bit
  * @param  lsbit (byte) low significant bit
  * @retval 32-bit value, content of specified bits
  */
uint32_t Read_Dword_Bits(uint8_t rd_opcode, uint8_t address, uint8_t msbit, uint8_t lsbit)
{
//#define _DEBUGGGING_FUNCTION
  
  uint32_t address_content = 0;
  uint32_t bit_amount = 0;
  uint32_t bit_mask = 0;
  uint32_t temp_u32 = 0;
  
  /* out of range [31:0] */
  if (msbit > 31) msbit = 31;
  if (lsbit > 31) lsbit = 31;
  
  if (lsbit > msbit) lsbit = msbit;
  
  /* build the mask */
  bit_amount = msbit - lsbit;
  for (int i = 0; i < bit_amount + 1; i++) {
    bit_mask <<= 1;
    bit_mask += 1;
  }
  bit_mask <<= lsbit;
  
  /* read the register content */
  address_content = Read_Dword(rd_opcode, address);
  temp_u32 = (address_content & bit_mask) >> lsbit;
  
#ifdef _DEBUGGGING_FUNCTION
  /* for debugging */
  puts("Read_Dword_Bits");
  printf(" RD opcode = 0x%02X\taddress = 0x%02X\n", rd_opcode, address);
  printf(" msb = %u\tlsb = %u\n", msbit, lsbit);
  printf(" read content (before) = 0x%08X\tread content (after) = 0x%08X\n", address_content, temp_u32);
  printf(" RD bit_mask = 0x%08X\n", bit_mask);
#endif
  
#undef _DEBUGGGING_FUNCTION
  
  return temp_u32;
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
