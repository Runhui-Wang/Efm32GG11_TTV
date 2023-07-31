/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    user_tools.c
  * @brief   Useful Tools and Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "user_tools.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
time_t t;
struct tm * ts;

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

/******************************************************************************/
/*                               Delay of 100us                               */
/******************************************************************************/
/**
  * @brief  This function creates delay in steps of 100us
  * @param  delay (uint32_t) duration in steps of 100 microsecond [100us]
  * @retval none
  */
void Delay_100us(uint32_t delay)
{
  uint32_t counter = 0;
  uint32_t adjust = 2000;
  
  delay *= adjust;
  
  while (counter < delay)
  {
    counter++;
  }
}

/******************************************************************************/
/*                    Two's Complement to Decimal Conversion                  */
/******************************************************************************/
/**
  * @brief  This function takes about ~88�s, using POW() two times! Means,
  *             each function call of POW() takes approx. 40�s AND header 
  *             file is needed! 
  *                     #include <tgmath.h>
  *                     [..]
  *                     exp = POW(2, bit);
  *                     half_exp = POW(2, bit-1);
  *
  *             ON THE OTHER HAND, using if-clauses, THIS function takes ~2�s
  *                     [..]
  *                     if (bit==16) exp = 65536;
  *                     half_exp = exp / 2;
  *
  *             Definition Two's Complement: Negative numbers in binary
  *                     Given a set of all possible N-bit values, we can assign
  *                     the lower (by the binary value) half to be the integers 
  *                     from 0 to (2^N-1 - 1) inclusive and the upper half to 
  *                     be (-2N-1) to -1 inclusive
  *
  *             Example:
  *                     // divided by 2^16 (fpp), multipled by 250ns (e.g. T_ref)
  *                     FLOAT_Value = Two_s_Complement_Conversion(HEX_value, 16, 250E-9); 
  *
  * @param  raw_number (uint32_t) 
  * @param  bit (int) 
  * @param  mult_factor (float) 
  * @retval Two's Complement (float)
  */
float Two_s_Complement_Conversion(uint32_t raw_number, int bit, float mult_factor)
{
  float number;
  double exp, half_exp;

  /* determine the 'power of 2' */
  if (bit==32) exp = 4294967296;  /* = 2^32 */
  if (bit==24) exp = 16777216;    /* = 2^24 */
  if (bit==16) exp = 65536;       /* = 2^16 */
  if (bit==8)  exp = 256;         /* = 2^8 */

  half_exp = exp / 2;
  
  number = raw_number / exp;

  if (number <= (half_exp - 1)) {
    /*positive number, nothing to do */
  } else { /**/
    /*to get negative number */
    number -= exp;
  }

  /*to get the correct result by multiplication factor */
  number *= mult_factor;
  
  return number;
}

/******************************************************************************/
/*                             Converts HEX to DEC                            */ 
/******************************************************************************/
/**
  * @brief  This function converts up to 8 hex characters (incl. character 0..9, 
  *             A..F, a..f) into corresponding decimal value.
  *             #include <string.h>
  *
  *             Example:
  *                     char* hex_str = "ba34F";
  *                     uint32_t dec_val = convert_hex2dec(hex_str);
  *                     printf("hex = 0x%s \tdec = %u \n", hex_str, dec_val);
  *
  *             Error Handling:
  *                     hex character > 8 --> return max value (0xFFFFFFFF)
  *                     undefined hex character --> return 0
  *
  * @param  char_input is the pointer of HEX-string, max. 8 characters
  * @retval integer value of corresponding decimal value
  */
int convert_hex2dec(char *char_input)
{
  int length = strlen(char_input);

  int final_val = 0;
  int dec_val = 0;
  int factor = 0;

  if (length > 8) {
    /* overloaded */
    return -1; /* 0xFFFF FFFF = 2^32 - 1 */
  }
  
  for (int i = 0; i < length; i++) {
    /* multiplication factor for related character*/
    if ((length-1) - i == 0) factor = 1;         /* 2^0 */
    if ((length-1) - i == 1) factor = 16;        /* 2^4 */
    if ((length-1) - i == 2) factor = 256;       /* 2^8 */
    if ((length-1) - i == 3) factor = 4096;      /* 2^12 */
    if ((length-1) - i == 4) factor = 65536;     /* 2^16 */
    if ((length-1) - i == 5) factor = 1048576;   /* 2^20 */
    if ((length-1) - i == 6) factor = 16777216;  /* 2^24 */
    if ((length-1) - i == 7) factor = 268435456; /* 2^28 */
    
    /* set value to zero*/
    dec_val = 0;
    
    /* in case ASCII character is not allowed - Error Handling */
    if (*char_input < 48 || (*char_input > 70 && *char_input < 97) || *char_input >102) return 0;
    
    /* convert ASCII code into decimal */
    if (*char_input == 48)                       dec_val =  0; /* char(0) */
    if (*char_input == 49)                       dec_val =  1; /* char(1) */
    if (*char_input == 50)                       dec_val =  2; /* char(2) */
    if (*char_input == 51)                       dec_val =  3; /* char(3) */
    if (*char_input == 52)                       dec_val =  4; /* char(4) */
    if (*char_input == 53)                       dec_val =  5; /* char(5) */
    if (*char_input == 54)                       dec_val =  6; /* char(6) */
    if (*char_input == 55)                       dec_val =  7; /* char(7) */
    if (*char_input == 56)                       dec_val =  8; /* char(8) */
    if (*char_input == 57)                       dec_val =  9; /* char(9) */
    if (*char_input == 65 || *char_input == 97)  dec_val = 10; /* char(A) */
    if (*char_input == 66 || *char_input == 98)  dec_val = 11; /* char(B) */
    if (*char_input == 67 || *char_input == 99)  dec_val = 12; /* char(C) */
    if (*char_input == 68 || *char_input == 100) dec_val = 13; /* char(D) */
    if (*char_input == 69 || *char_input == 101) dec_val = 14; /* char(E) */
    if (*char_input == 70 || *char_input == 102) dec_val = 15; /* char(F) */
  
    dec_val *= factor;
    final_val += dec_val;
    
    char_input++;
  }
  
  return final_val;
}

/******************************************************************************/
/*                          Converts Gray to Decimal                          */ 
/******************************************************************************/
/**
  * @brief  Converts 2-bit gray code to decimal
  *         Definition of Gray code, also known as reflected binary code,
  *             is a code having digits 0 and 1. Gray code do not have place 
  *             value for its digits. Any successive codes in Gray code system 
  *             have only one bit changes.
  *
  *         Error Handling:
  *             gray code is not allowed --> return 99
  *
  * @param  gray_input (integer)
  * @retval decimal
  */
int convert_gray2dec(int gray_input)
{
  int dec_val = 0;
  
  /* in case gray code is not allowed - Error Handling */
  if (gray_input < 0 || gray_input > 3) return 99; 
   
  if (gray_input == 0) dec_val = 0; /* Gray Code 00 (dec. 0) --> 0 */
  if (gray_input == 1) dec_val = 1; /* Gray Code 01 (dec. 1) --> 1 */
  if (gray_input == 3) dec_val = 2; /* Gray Code 11 (dec. 3) --> 2 */
  if (gray_input == 2) dec_val = 3; /* Gray Code 10 (dec. 2) --> 3 */

  return dec_val;
}

/******************************************************************************/
/*                          Converts Float to String                          */ 
/******************************************************************************/
/**
  * @brief  This function converts the double value passed in val into an ASCII 
  *             representation that will be stored under sout. The caller is 
  *             responsible for providing sufficient storage in sout.
  *
  *         Conversion is done in the format "[-]d.ddd". The minimum field 
  *             width of the output string (including the possible '.' and the 
  *             possible sign for negative values) is given in width, and prec 
  *             determines the number of digits after the decimal sign. width 
  *             is signed value, negative for left adjustment.
  *
  *         Example:
  *             dtostrf(Value*1E9, 7, 3, string);
  *
  * @param  val (double)
  * @param  width (signed char)
  * @param  prec (unsigned char)
  * @param  sout (char) pointer to the converted string sout
  * @retval decimal
  */
char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {

  char fmt[20];

  sprintf(fmt, "%%%d.%df", width, prec);

  sprintf(sout, fmt, val);

  return sout;

}

/******************************************************************************/
/*                      Print current date on Terminal IO                     */
/******************************************************************************/
/**
  * @brief  This function prints current date on Terminal IO
  * @retval none
  */



/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */


/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
