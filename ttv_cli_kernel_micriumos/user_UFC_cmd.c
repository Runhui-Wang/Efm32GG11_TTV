/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    user_UFC_cmd.c
  * @brief   UFC Sequence Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#define UFC_DEVICE_AS6031

#include "user_UFC_cmd.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "user_spi_interface.h"
#include "user_tools.h"
#include "spidrv.h"
#include "sl_spidrv_instances.h"
#include <stdint.h>
#include <os.h>
#include "user_AS6031_parameter.h"
#include "sl_sleeptimer.h"

#define SPI_HANDLE                  sl_spidrv_exp_handle


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

//#define BLOCKSIZE_MAX 128  //related to GP30 
#if defined(UFC_DEVICE_GP30)
	#define BLOCKSIZE_MAX 128
#elif defined(UFC_DEVICE_AS6031)
	#define BLOCKSIZE_MAX 1024
#else
#define BLOCKSIZE_MAX 64 //default
#endif

RTOS_ERR idle_err;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

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


void callback2(){
  OSTimeDly( 10,
                 OS_OPT_TIME_DLY,
                 &idle_err);
  return;
}
/******************************************************************************/
/*              Waiting for Interrupt and reading Interrupt Flag              */ 
/******************************************************************************/
/**
  * @brief  This function waits for interrupt and reads the interrupt flag.
  * @retval none
  */
void Waiting_For_INTN_Flag2(int flag_no, uint32_t timeout)
{
  //#define _DEBUGGGING_FUNCTION
  uint32_t tickstart;
  
  /* Init tickstart for timeout management */
  tickstart = sl_sleeptimer_get_tick_count64();

  /* step a - Waiting for the interrupt INTN (low active) */
  while(GPIO_PinInGet(gpioPortA, 12))
  {
    /* Timeout management */
    if ((((sl_sleeptimer_get_tick_count64() - tickstart) >=  timeout) && (timeout != 0xFFFFFFFFU)) || (timeout == 0U))
    {
#ifdef _DEBUGGGING_FUNCTION
      printf("TIMEOUT after %u ms\n", timeout);
      printf("Bit No. %u are not detected\n", flag_no);
#endif
#undef _DEBUGGGING_FUNCTION
      return;
    }
  }
  
  /* step b - Cleck interrupt flag on reading SRR_IRQ_FLAG */
  int interrupt = 0;
  int check_int_mask = 0;
  if (flag_no == 0) {check_int_mask = TSQ_FNS_mask;}
  if (flag_no == 1) {check_int_mask = FW_TRANS_FNS_mask;}
  if (flag_no == 2) {check_int_mask = BLD_FNS_mask;}
  if (flag_no == 3) {check_int_mask = CHKSUM_FNS_mask;}
  if (flag_no < 0 || flag_no > 3) {Write_Opcode(RC_IF_CLR); return;}
  do {
    interrupt = Read_Dword(RC_RAA_RD_RAM, 0xE0);
    interrupt &= check_int_mask;  
  } while (interrupt != check_int_mask);
  
  /* step c - Clear interrupt flag register by sending RC_IF_CLR */
  Write_Opcode(RC_IF_CLR);
}

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*             Waiting for interrupt with polling of System Status            */
/******************************************************************************/
/**
  * @brief  Waiting for interrupt.
  * @param  Timeout Timeout duration
  * @retval none
  */
void Waiting_For_INTN_Poll_Status(uint32_t timeout)
{
  uint32_t tickstart;
  //uint8_t spiRX[0];
  
  /*Init tickstart for timeout management */
  tickstart = sl_sleeptimer_get_tick_count64();

  /*step a - Waiting for the interrupt INTN (low active) */
  while(GPIO_PinInGet(gpioPortA, 12))
  {
    /* Polling of System Status byte */
    //spiRX[0] = System_Status();
    
    /* Post precessing of System Status */
    /* ...in progress */
    
    /* Timeout management */
    if ((((sl_sleeptimer_get_tick_count64() - tickstart) >=  timeout) && (timeout != 0xFFFFFFFFU)) || (timeout == 0U))
    {
      printf("TIMEOUT after %u ms\n", (unsigned int)timeout);
    }
  }
}
#endif

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*               Sending System Reset (incl. reseting RST_FLAG)               */ 
/******************************************************************************/
/**
  * @brief This function performs a System Reset and waits for the interrupt,
  *             checking RST Flag with additional clearing of this flag.
  * @retval none
  */
void Sending_System_Reset(void)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 20; 
  
  /* sending system reset */
  Write_Opcode(RC_SYS_RST);
  /* check boot loading sequence has been finished, bit 2 */
  Waiting_For_INTN_Flag2(2, timeout);
  /* reset RST_FLAG */
  Write_Opcode(RC_RF_CLR);
}
#endif

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*                       Sequence: Erase complete NVRAM                       */ 
/******************************************************************************/
/**
  * @brief This function shows the whole sequence of erasing NVRAM completely 
  *             on TERMINAL I/O.
  * @retval none
  */
void Sequence_Erase_NVRAM(void)
{
  /* Start with System Reset */
  puts("START of initial FW Programming with System Reset");
  Start_with_System_Reset();
  
  /* Preparation */
  puts("- Preparation");
  Preparation();
  
  /* Erase FW Code and FW Data */
  puts("- Erase FW Code and FW Data");
  Erase_FWC_FWD();
  
  /* Retention Check */
  puts("- Retention Check");
  if (!FW_Retention_Check()) {
    puts("\t...CHECK: PASS\n");
  } else {
    puts("\t...CHECK: FAIL\n");
  }
}
#endif

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*        Sequence: Download FWC and FWD (incl. LOCKED and NOT_LOCKED)        */ 
/******************************************************************************/
/**
  * @brief  This function shows the whole sequence of downloading FW Code 
  *             and FW Data on TERMINAL I/O.
  * @param  fwcode pointer of 8-bit array
  * @param  fwc_size 32-bit value determines the size of the array
  * @param  fwdata pointer of 32-bit array with size of 128
  * @param  lock specifies the state of the NVRAM after writing
  *            @arg NOT_LOCKED: to have READ/WRITE ACCESS to FWDU, CR-Register
  *                             and ONLY WRITE ACCESS to FWCU
  *            @arg LOCKED: to have ONLY WRITE ACCESS to FWDU, CR-Register
  *                             and NO ACCESS to FWCU
  * @retval none
  */
void Sequence_Download_FWC_FWD(uint8_t *fwcode, uint32_t fwc_size, uint32_t *fwdata, uint8_t lock)
{
  /* Start with System Reset */
  puts("START of initial FW Programming with System Reset");
  Start_with_System_Reset();
 
  /* Preparation */
  puts("- Preparation");
  Preparation();
  
  /* Download FW Code and FW Data including LOCKED or NOT_LOCKED */
  puts("- Write-Store (& Lock) FW Code and FW Data");
  Download_FWC_FWD(fwcode, fwc_size, fwdata, lock);
  
  /* Retention Check */
  puts("- Retention Check");
  if (!FW_Retention_Check()) {
    puts("\t...CHECK: PASS\n");
  } else {
    puts("\t...CHECK: FAIL\n");
  }
}
#endif

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*                           Sequence: Download FWD                           */ 
/******************************************************************************/
/**
  * @brief  This function shows the whole sequence of downloading FW Data only 
  *             on TERMINAL I/O.
  * @param  fwdata pointer of 32-bit array with size of 128
  * @retval none
  */
void Sequence_Download_FWD(uint32_t *fwdata)
{
  /* Start with System Reset */
  puts("START of initial FW Programming with System Reset");
  Start_with_System_Reset();
  
  /* Preparation */
  puts("- Preparation");
  Preparation();
  
  /* Download FW Data only */
  puts("- Write-Store FW Data only");
  Download_FWD_ONLY(fwdata);
  
  /* Retention Check */
  puts("- Retention Check");
  if (!FW_Retention_Check()) {
    puts("\t...CHECK: PASS\n");
  } else {
    puts("\t...CHECK: FAIL\n");
  }
}
#endif

/******************************************************************************/
/*           Start with System Reset (incl. mandatory waiting time)           */ 
/******************************************************************************/
/**
  * @brief This function starts with System Reset, incl. mandatory waiting time.
  * @retval none
  */
void Start_with_System_Reset(void)
{
  /* STEP 1 - Sending SYS_RST */
  Write_Opcode(RC_SYS_RST);
  
  /* STEP 2 - Mandatory wait time: At least 0.8 ms */
  Delay_100us(8);
}

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*                        Read double word with status                        */
/******************************************************************************/
/**
  * @brief  Read double word.
  * @param  opcode (byte)
  * @param  address (byte)
  * @retval 32-bit value
  */
uint32_t Read_Dword_with_Status(uint8_t rd_opcode, uint8_t address)
{
//#define _DEBUGGGING_FUNCTION
  
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10;
  uint8_t spiTX_pre[2];
  uint8_t spiTX_post[1];
  uint8_t spiRX[4];
  uint8_t spiRX_preSYS[1];
  uint8_t spiRX_postSYS[1];
  uint32_t temp_u32 = 0;
  
  uint8_t same_SYS_bits = 0;
  uint8_t all_SYS_bits = 0;
  uint8_t pre_SYS_bits = 0;
  uint8_t post_SYS_bits = 0;
  //uint8_t pre_MT_REQ_CTR = 0; //variable 'post_MT_REQ_CTR' set but not used [-Wunused-but-set-variable]
  //uint8_t post_MT_REQ_CTR = 0; //variable 'post_MT_REQ_CTR' set but not used [-Wunused-but-set-variable]
  
  int run_pass;
  int well_done;

  spiTX_pre[0] = rd_opcode;
  spiTX_pre[1] = address;
  spiTX_post[0] = RC_RD_STATUS;
  
  uint8_t error_mask = 0;
  
  if (rd_opcode==RC_RAA_RDS_RAM || rd_opcode==RC_RAA_RDS_NVRAM) {
  run_pass = 1;  
    
    do {
      /* 1. Put SSN low - Activate */
      Set_SSN(LOW);
      
      /* 2. Transmit register address */
      SPIDRV_MTransmit  (SPI_HANDLE,
      spiTX_pre,
      2,
      callback2
      );
      /* 3. Read four bytes with System Status byte first */
      SPIDRV_MReceive  (SPI_HANDLE,
      spiRX_preSYS,
      1,
      callback2
      );
      SPIDRV_MReceive  (SPI_HANDLE,
      spiRX,
      4,
      callback2
      );
      
      /* 4. Put SSN high - Deactivate */
      Set_SSN(HIGH);
      
      /* tpwssn = serial clock time period (tsck = 125 ns) */
      /* SSN pulse width between two cycles */
      
      /* 5. Read System Status at the end */
      /* 5.1 Put SSN low - Activate */
      Set_SSN(LOW);
      
      /* 5.2 Transmit register address */
      SPIDRV_MTransmit  (SPI_HANDLE,
                         spiTX_post,
           1,
           callback2
           );
      
      /* 5.3 Read only System Status byte */
      SPIDRV_MReceive  (SPI_HANDLE,spiRX_postSYS,1,callback2 );
      
      /* 5.4 Put SSN high - Deactivate */
      Set_SSN(HIGH);
      
      /* Evaluation of System Status (pre- and post-) */
      /* Defintion of System Status Error */
      error_mask = 0xE3; /* 1110 0011 */

      /* [Bit0]   0x01 -> RAA_BUSY (internal processes ongoing)          */
      /* [Bit1]   0x02 -> TSQ_BUSY_PRED (remaining idle time prediction) */
      /* [Bit3:2] 0x0C -> MT_REQ_CTR (Measure Task Reuest Counter)       */
      /* [Bit4]   0x10 -> MCT_STATE (Status of Measure Cycle Timer)      */
      /* [Bit5]   0x20 -> COM_FAIL (Communication Failed)                */
      /* [Bit6]   0x40 -> RST_FLAG (clear RST_FLAG after reading)        */
      /* [Bit7]   0x80 -> ERR_FLAG (only one bit in 0xE1 is set)         */

      /* Comparision of System Status (spiRX_preSYS and spiRX_postSYS) */
      same_SYS_bits = (spiRX_preSYS[0] & spiRX_postSYS[0]);
      all_SYS_bits = (spiRX_preSYS[0] | spiRX_postSYS[0]);
      pre_SYS_bits = spiRX_preSYS[0] - same_SYS_bits;
      post_SYS_bits = spiRX_postSYS[0] - same_SYS_bits;
      
      //pre_MT_REQ_CTR = convert_gray2dec((spiRX_preSYS[0]&0x0C)>>2);
      //post_MT_REQ_CTR = convert_gray2dec((spiRX_postSYS[0]&0x0C)>>2);
      
      
      printf("(%02X:%02X:%02X:%02X)", all_SYS_bits, pre_SYS_bits, same_SYS_bits, post_SYS_bits);
      if (((spiRX_preSYS[0] & error_mask) != 0) || ((spiRX_postSYS[0] & error_mask) != 0)) {
        /* Error Handling - system status shows errors */
        
//        printf(" ");
//        
//        /* PRE SYSTEM STATUS */
//        /* ----------------- */
//        /* RAA_BUSY is set -> ... */
//        if ((spiRX_preSYS[0]&0x01) != 0) {
//          printf("A");
//        }
//
//        /* TSQ_BUSY_PRED is set -> ... */
//        if ((spiRX_preSYS[0]&0x02) != 0) {
//          printf("B");
//        }
//        
//        /* COM_FAIL is set -> ... */
//        if ((spiRX_preSYS[0]&0x20) != 0) {
//          printf("C");
//        }
//        
//        /* RST_FLAG is set -> ... */
//        if ((spiRX_preSYS[0]&0x40) != 0) {
//          printf("D");
//        }
//        
//        /* ERR_FLAG is set -> ... */
//        if ((spiRX_preSYS[0]&0x80) != 0) {
//          printf("E");
//        }
//
//        /* POST SYSTEM STATUS */
//        /* ------------------ */
//        /* RAA_BUSY is set -> ... */
//        if ((spiRX_postSYS[0]&0x01) != 0) {
//          printf("a");
//        }
//
//        /* TSQ_BUSY_PRED is set -> wait at least USM_PAUSE (20ms) */
//        if ((spiRX_postSYS[0]&0x02) != 0) {
////          HAL_Delay(2); /* delay of 20ms */
//          printf("b");
//        }
//        
//        /* COM_FAIL is set -> ... */
//        if ((spiRX_postSYS[0]&0x20) != 0) {
//          printf("c");
//        }
//        
//        /* RST_FLAG is set -> ... */
//        if ((spiRX_postSYS[0]&0x40) != 0) {
//          printf("d");
//        }
//        
//        /* ERR_FLAG is set -> ... */
//        if ((spiRX_postSYS[0]&0x80) != 0) {
//          printf("e");
//        }

#ifdef _DEBUGGGING_FUNCTION
        printf("x=%02X<>%02X ", spiRX_preSYS[0], spiRX_postSYS[0]);
        /* repeat reading with fixed delay */
//        HAL_Delay(1); /* delay of 1ms */
        Delay_100us(10); /* delay of 1ms */
#endif
        
        /* counts the processes */
        run_pass++;
        
        well_done = 0;
      } else {
        /* both system status without any errors */
        well_done = 1;
      }
      
    } while (well_done == 0); /* end of do{}-while loop */
    
    /* reading without any errors */
    printf(", Run = %u, ", run_pass);
    puts("RD OK");
    
  } else {
    /* 1. Put SSN low - Activate */
    Set_SSN(LOW);
    
    /* 2. Transmit register address */
    SPIDRV_MTransmit  (SPI_HANDLE,spiTX_pre,2,callback2 );
      
    /* 3. Read four bytes */
    SPIDRV_MReceive  (SPI_HANDLE,spiRX,4,callback2 );

    /* 4. Put SSN high - Deactivate */
    Set_SSN(HIGH);
  }
  
  /*Concatenate of bytes (from MSB to LSB) */
  temp_u32 = (spiRX[0]<<24) + (spiRX[1]<<16) + (spiRX[2]<<8) + (spiRX[3]);
  
#undef _DEBUGGGING_FUNCTION
  
  return temp_u32;
}
#endif

/******************************************************************************/
/*                           Perform FW Transaction                           */ 
/******************************************************************************/
/**
  * @brief This function performs FW transaction.
  * @retval none
  */
void Perform_FW_Transaction(int shr_rc_bit)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 100; 
  /* STEP a - Enable FW Transaction */
#ifdef UFC_DEVICE_AS6031
  Write_Dword(RC_RAA_WR_RAM, SHR_RC_RLS, 0x50F5B8CA);
#else
  Write_Dword(RC_RAA_WR_RAM, SHR_FW_TRANS_EN, 0x50F5B8CA);  
#endif

  
  /* STEP b - Execute FW Transaction by writing code to SHR_RC(bit x) */
  if (shr_rc_bit == 16) Write_Dword(RC_RAA_WR_RAM, SHR_RC, 0x00010000);  //Bit 16, FW Store All
  if (shr_rc_bit == 17) Write_Dword(RC_RAA_WR_RAM, SHR_RC, 0x00020000);  //Bit 17, FW Store & Lock All
  if (shr_rc_bit == 18) Write_Dword(RC_RAA_WR_RAM, SHR_RC, 0x00040000);  //Bit 18, FW Erase
  if (shr_rc_bit == 19) Write_Dword(RC_RAA_WR_RAM, SHR_RC, 0x00080000);  //Bit 19, FW Code Recall
  if (shr_rc_bit == 20) Write_Dword(RC_RAA_WR_RAM, SHR_RC, 0x00100000);  //Bit 20, FW Data Recall
  if (shr_rc_bit == 21) Write_Dword(RC_RAA_WR_RAM, SHR_RC, 0x00200000);  //Bit 21, FW Code Store
  if (shr_rc_bit == 22) Write_Dword(RC_RAA_WR_RAM, SHR_RC, 0x00400000);  //Bit 22, FW Data Store
  
  /* STEP c - Check on interrupt FW_TRANS_FNS */
  Waiting_For_INTN_Flag2(1, timeout);
}

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*                                 Preparation                                */ 
/******************************************************************************/
/**
  * @brief  This function prepairs the device for initial FW programming.
  * @retval none
  */
void Preparation(void)
{
  /* STEP 1 - Request Bus Master */
  Write_Opcode(RC_BM_REQ);
    
  /* STEP 2 - Disable Watchdog */
  Write_Dword(RC_RAA_WR_RAM, 0xC0, 0x48DBA399);

  /* STEP 3 - Set RESTART_EN by writing code to CR_TRIM2 */
  Write_Dword(RC_RAA_WR_RAM, 0xCD, 0x40100000);

  /* STEP 4 - Disable BG & Charge Pump settings in CR_MR_TS */
  Write_Dword(RC_RAA_WR_RAM, 0xC6, 0x00000000);

  /* STEP 5 - Execute Supervisor Init by sending RC_SV_INIT */
  Write_Opcode(RC_SV_INIT);
    
  /* STEP 6 - Mandatory wait time: At least 0.2 ms */
  Delay_100us(2);
    
  /* STEP 7 - Request Dummy Measurement Task */
  Write_Opcode2(RC_MT_REQ, 0x00);
    
  /* STEP 8 - Mandatory wait time: At least 0.5 ms */
  Delay_100us(5);
    
  /* STEP 9 - clear all flags */
  Write_Dword(RC_RAA_WR_RAM, SHR_EXC, 0x0000007);
    
  /* STEP 10 - reset RST_FLAG */
  Write_Opcode(RC_RF_CLR);
    
  /* STEP 11 - Release Bus Master */
  Write_Opcode(RC_BM_RLS);
}
#endif

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*         Evaluation of Preparation() with additional Aribitrary Time        */ 
/******************************************************************************/
/**
  * @brief  This function evaluates Preparation() with additional 
  *             aribitrary time.
  * @retval none
  */
void Preparation_Eval(void)
{
  /* Repeat sequence with increased Arbitrary IDLE time in units of 100us */
  int loop_from        = 1;     /* with step size of 0.1ms */
  int first_limit      = 300;   /* first limit in units of 0.1ms*/
  int second_step_size = 50;    /* after fist limit, second step size is used */
  int loop_to          = 3000;  /* the end */
  
  int polling_time_ms  = 20000; /* e.g. 20 second */
  
  /**
    * Calculation of processing time [s]
    *
    *                            (loop_to - first_limit)     polling_time_ms
    * time [s] = ( first_limit + ----------------------- ) * ---------------
    *                               second_step_size              1000
    *
    */
  
  for (int i = loop_from; i < loop_to + 1; )
  {
    printf("\tArbitrary Time = %0.1f ms\n", ((float)(i)/10));
    
    /* STEP 0 - Arbitrary time (0.1ms - 30ms) */
    Delay_100us(i);

    Preparation();

    if (i >= loop_to)
    {
      return;
    } else {
      /* STEP (last+1)a - Polling System Status during Arbitrary time (20s) */
      SYS_Status_Delay(polling_time_ms);
      
      /* STEP (last+1)b - Sending SYS_RST */
      Write_Opcode(RC_SYS_RST);

      /* STEP (last+1)c - Mandatory wait time: At least 0.8 ms */
      Delay_100us(8);
      
      /* STEP (last+1)d - reset RST_FLAG */
      Write_Opcode(RC_RF_CLR);
    }

    /* increase step size in dependency of the time sequence */
    if (i < first_limit)
    {
      i++; /* step size = 0.1 ms until first_limit */
    } else {
      i += second_step_size; /* e.g. step size = 5 ms */
    } 
    
  } /* end i-loop */
}
#endif

/******************************************************************************/
/*                        Download FW Code and FW Data                        */ 
/******************************************************************************/
/**
  * @brief  This function writes and stores/locks FW Code and FW Data.
  * @param  fwcode pointer of 8-bit array
  * @param  fwc_size 32-bit value determines the size of the array
  * @param  fwdata pointer of 32-bit array with size of 128
  * @param  lock specifies the state of the NVRAM after writing
  *            @arg NOT_LOCKED: to have READ/WRITE ACCESS to FWDU, CR-Register
  *                             and ONLY WRITE ACCESS to FWCU
  *            @arg LOCKED: to have ONLY WRITE ACCESS to FWDU, CR-Register
  *                             and NO ACCESS to FWCU
  * @retval none
  */
void Download_FWC_FWD(uint8_t *fwcode, uint32_t fwc_size, uint32_t *fwdata, uint8_t lock)
{
  /* STEP 1 - Get range of FW user code */
  FWU_RNG = Read_Dword(RC_RAA_RD_RAM, SRR_FWU_RNG);
  
  /* STEP 2 - Enable important interrupt flags */
  Write_Dword(RC_RAA_WR_RAM, 0xC4, 0x00020000);

  /* STEP 3 - Perfom Recall of FW Code */
  Perform_FW_Transaction(19);
  
  /* STEP 4 - Perfom Recall of FW Data */
  Perform_FW_Transaction(20);

  /* STEP 5 - Write Firmware Code */
  Write_FWC((uint8_t *)fwcode, fwc_size);
  
  /* STEP 6 - Write Firmware Data to FWD address 2-119 (0-119) */
  Write_Dword_Auto_Incr(RC_RAA_WR_NVRAM, 2, (uint32_t *)fwdata, 119);
  
  /* STEP 7 - Checksum Calculation, write expected checksums to FWD address 0-1 */
  FWCU_CS_by_SW = Calc_Checksum_FWC((uint8_t *)fwcode, fwc_size);
  Write_Dword(RC_RAA_WR_NVRAM, 0x00, FWCU_CS_by_SW);
  
  FWDU_CS_by_SW = Calc_Checksum_FWD((uint32_t *)fwdata, 2, 119);
  Write_Dword(RC_RAA_WR_NVRAM, 0x01, FWDU_CS_by_SW);
  
  /* STEP 8 - Execute FW_STORE / FW_STORE_LOCK */
  /* Storing completely */
  if (lock == NOT_LOCKED) {
    Perform_FW_Transaction(16); /* Bit 16, FW_STORE_ALL */
  }
  
  /* Storing and locking FW completely */
  if (lock == LOCKED) {
    Perform_FW_Transaction(17); /* Bit 17, FW_STORE_LOCK */
  }

}

/******************************************************************************/
/*                            Download FW Data only                           */ 
/******************************************************************************/
/**
  * @brief This function writes and stores FW Data only.
  * @param  fwdata pointer of 32 bit array
  * @retval none
  */
void Download_FWD_ONLY(uint32_t *fwdata)
{
  /* STEP 1 - Enable important interrupt flags */
  Write_Dword(RC_RAA_WR_RAM, 0xC4, 0x00020000);

  /* STEP 2 - Perfom Recall of FW Data */
  Perform_FW_Transaction(20);
  
  /* STEP 3 - Write Firmware Data User FWDU to FWD addresses 2-119 (1�119) */
  Write_Dword_Auto_Incr(RC_RAA_WR_NVRAM, 2,(uint32_t *)fwdata, 119);

  /* STEP 4 - Checksum Calculation, write expected checksums to FWD address 1 */
  FWDU_CS_by_SW = Calc_Checksum_FWD((uint32_t *)fwdata, 2, 119);
  Write_Dword(RC_RAA_WR_NVRAM, 0x01, FWDU_CS_by_SW);
  
  /* STEP 5 - Execute FWD_STORE */
  Perform_FW_Transaction(22); /* Bit 22, FWD_STORE */
}

/******************************************************************************/
/*                          Erase FW Code and FW Data                         */ 
/******************************************************************************/
/**
  * @brief  This function erases the FW Code and FW Data.
  * @retval none
  */
void Erase_FWC_FWD(void)
{
  /* STEP 1 - Enable important interrupt flags */
  Write_Dword(RC_RAA_WR_RAM, 0xC4, 0x00020000);

  /* STEP 2 - Perform Erase of Firmware Code & Data */
  Perform_FW_Transaction(18);  /* Bit 18, FW_ERASE */
}

/******************************************************************************/
/*                             FW Retention Check                             */ 
/******************************************************************************/
/**
  * @brief  This function checks the storage into NVRAM.
  * @retval integer value
  *             return 0: Retention Check - PASS
  *             return 1: Retention Check - FAIL
  */
int FW_Retention_Check(void)
{
  /* Timeout duration in millisecond [ms] */
  uint16_t timeout = 1000;
  
  /* STEP 1 - Enable important interrupt flags */
  Write_Dword(RC_RAA_WR_RAM, 0xC4, 0x000A0000);

  /* STEP 2 - Perfom Recall of FW Code */
  Perform_FW_Transaction(19);  /* Bit 19, FWC_RECALL */
  
  /* STEP 3 - Perfom Recall of FW Data */
  Perform_FW_Transaction(20);  /* Bit 19, FWD_RECALL */
  
  /* STEP 4 - Initialize checksum error flags in SHR_GP0 */
  Write_Dword(RC_RAA_WR_RAM, SHR_GPO, 0x0007F000);  /* Bit[18:12] */
  
  /* STEP 5 - Builds checksum of all FW memories */
  Write_Opcode(RC_FW_CHKSUM);

  /* STEP 6 - Check on interrupt CHKSUM_FNS */
  Waiting_For_INTN_Flag2(3, timeout);
  
  /* STEP 7 - Retention check by reading SHR_GP0 */
  if (Reading_SHR_GPO() == 0)
  {
    /* Check: PASS */
    return 0; 
  } else {
    /* Check: FAIL */
    return 1; 
  }
}

/******************************************************************************/
/*                    Reading System Handling Register GP0                    */ 
/******************************************************************************/
/**
  * @brief  This function handles Non maskable interrupt.
  * @retval Retention Check as integer value
  *             0 := PASS
  *             1 := FAIL
  */
int Reading_SHR_GPO(void)
{
  uint32_t Retention_Check = 0;
  uint32_t Retention_Check_mask = 0x0007F000; //Bit[18:12]
  
  Retention_Check = Read_Dword(RC_RAA_RD_RAM, SHR_GPO);
  Retention_Check &= Retention_Check_mask;
  
  if (Retention_Check == 0) {
    /* PASS: SHR_GP0[18:12] == b0000000 */
    return 0;
  } else {
    /* FAIL: SHR_GP0[18:12] != b0000000 */
    return 1;
  }
}

/******************************************************************************/
/*                     Print System Handling Register GP0                     */ 
/******************************************************************************/
/**
  * @brief  This function prints System Handling Register GP0 on TERMINAL I/O.
  * @retval None
  */
void Printf_SHR_GPO(void)
{
  uint32_t Retention_Check = 0;
  uint32_t Retention_Check_mask = 0x0007F000; //Bit[18:12]
  
  Retention_Check = Read_Dword(RC_RAA_RD_RAM, SHR_GPO);
  Retention_Check &= Retention_Check_mask;
  
  printf("System Handling Register GP0 [bit 18:12] = 0x%08X\n", (unsigned int)Retention_Check);
  
  if (Retention_Check != 0) {
    /* FAIL: SHR_GP0[18:12] != b0000000 */
    if ((Retention_Check & 0x01000)!=0) printf(" [Bit12] -> FWCU_CSE\n"); //bit12 
    if ((Retention_Check & 0x02000)!=0) printf(" [Bit13] -> FWDU_CSE\n"); //bit13 
    if ((Retention_Check & 0x04000)!=0) printf(" [Bit14] -> FWCA_CSE\n"); //bit14 
    if ((Retention_Check & 0x08000)!=0) printf(" [Bit15] -> FWDA_CSE\n"); //bit15 
    if ((Retention_Check & 0x10000)!=0) printf(" [Bit16] -> FWCU_TRE\n"); //bit16 
    if ((Retention_Check & 0x20000)!=0) printf(" [Bit17] -> FWCA_TRE\n"); //bit17 
    if ((Retention_Check & 0x40000)!=0) printf(" [Bit18] -> FWD_TRE\n");  //bit18 
  }
}

/******************************************************************************/
/*                                Write FW Code                               */ 
/******************************************************************************/
/**
  * @brief  This function writes FW Code and fills up with zero.
  * @param  fwcode pointer of 32-bit array
  * @param  fwc_size 32-bit value indicates the end of the 32-bit array
  * @retval none
  */
void Write_FWC(uint8_t *fwcode, uint32_t fwc_size)
{
  /* Write FW Code completely */
  Write_FWC_Auto_Incr(0x00, (uint8_t *)fwcode, fwc_size);
  
  /* Get the range of FW User Code and fill up with 0x00 up to FWU_RNG */
  FWU_RNG = Read_Dword(RC_RAA_RD_RAM, SRR_FWU_RNG);

  /* Write Array of zero blockwise after writing FW Code */
  Fill_Up_FWC_with_Zero(fwc_size);
}

/******************************************************************************/
/*                          Fill up FW Code with zero                         */ 
/******************************************************************************/
/**
  * @brief  This function fills up the rest of the NVRAM with zeros, beginning
  *             after the end of the FW Code.
  *         The storable area is maximum from 0x20 to FWU_RNG and 
  *             only this area influences the checksum.
  * @param  from_address interger value, fills up until FWU_RNG
  * @retval none
  */
void Fill_Up_FWC_with_Zero(uint16_t from_address)
{
  uint8_t zero_array[BLOCKSIZE_MAX];

  for (int i = 0; i < BLOCKSIZE_MAX; i++) {
    zero_array[i] = 0x00;
  }
  
  for (int i = from_address; i < FWU_RNG; ) {
    if (FWU_RNG - i > BLOCKSIZE_MAX) {
      Write_FWC_Auto_Incr(i, zero_array, BLOCKSIZE_MAX);
      /* next block */
      i += BLOCKSIZE_MAX;
    } else {
      Write_FWC_Auto_Incr(i, zero_array, FWU_RNG - i);
      /* last block */
      i += FWU_RNG - i;
    }
  }
}

/******************************************************************************/
/*                        Write FWC auto incrementally                        */ 
/******************************************************************************/
/**
  * @brief  This function writes the FW Code auto incrementally.
  * @param  address 16-bit value determines the starting address
  * @param  byte_array pointer of 8-bit array
  * @param  limit integer value determines the end of the array
  * @retval none
  */
void Write_FWC_Auto_Incr(uint16_t address, uint8_t *byte_array, int limit)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10; 

  uint8_t spiTX[3];
  uint8_t opcode = RC_FWC_WR;
  uint8_t address_MSB = address>>8;
  uint8_t address_LSB = address;
  
  spiTX[0] = opcode;
  spiTX[1] = address_MSB;
  spiTX[2] = address_LSB;
  
  /* 1. Put SSN low - Activate */
  Set_SSN(LOW);
  
  /* 2.a Transmit register address */
  SPIDRV_MTransmit  (SPI_HANDLE,spiTX,3,callback2 );

    
  /* 2.b Transmit register address */
  SPIDRV_MTransmit  (SPI_HANDLE,byte_array,limit,callback2 );

  /* 3. Put SSN high - Deactivate */
  Set_SSN(HIGH);
}

/******************************************************************************/
/*                         Calculate Checksum FW Code                         */ 
/******************************************************************************/
/**
  * @brief  This function calculates the checksum 8-bit array.
  * @param  byte_array pointer of 8-bit array
  * @param  array_size integer value determines the end of the array
  * @retval 32-bit value calculated checksum
  */
uint32_t Calc_Checksum_FWC(uint8_t *byte_array, int array_size)
{
  uint32_t sum = 0;
  
  for (int i = 0; i < array_size; i++)
  {
    /* First 32 Byte are NOT written into memory */
    if (i > 31)
    {
      sum += *byte_array;
    }
    byte_array++;
  }
  
  return sum;
}

/******************************************************************************/
/*                         Calculate Checksum FW Data                         */ 
/******************************************************************************/
/**
  * @brief  This function calculates the checksum 32-bit array.
  * @param  dword_array pointer of 32-bit array
  * @param  from_addr integer value determines the first address
  * @param  to_addr integer value determines the last address
  * @retval 32-bit value calculated checksum
  */
uint32_t Calc_Checksum_FWD(uint32_t *dword_array, int from_addr, int to_addr)
{
  uint32_t sum = 0;
  uint8_t temp[4] = {0,0,0,0};
  
  /* to start at expected index */
  dword_array += from_addr;
  
  for (int i = from_addr; i <= to_addr; i++)
  {
    /* reduce dword_array in separate bytes */
    temp[0]=*dword_array>>24;
    temp[1]=*dword_array>>16;
    temp[2]=*dword_array>>8;
    temp[3]=*dword_array;
    
    /* Checksum Calculation bytewise */
    sum += temp[0];
    sum += temp[1];
    sum += temp[2];
    sum += temp[3];
    
    dword_array++;
  }
  
  return sum;
}

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*                        Updating Checksum parameters                        */ 
/******************************************************************************/
/**
  * @brief  This function updates the Checksum parameters.
  * @param  fwcode pointer of 8-bit array
  * @param  fwc_size 32-bit value determines the size of the array
  * @param  fwdata pointer of 32-bit array with size of 128
  * @retval none
  */
void Update_Checksum(uint8_t *fwcode, uint32_t fwc_size, uint32_t *fwdata)
{
  // NOTE:
  // This sequence is from GP30 and was slightly adjusted/adapted.
  // Usage for GP31 (or higher variant) is NOT RELEASED!
  
  uint32_t interrupt;
  uint32_t config_c4;
  
  // calculate Checksum by SW
  FWCU_CS_by_SW = Calc_Checksum_FWC((uint8_t *)fwcode, fwc_size);
  FWDU_CS_by_SW = Calc_Checksum_FWD((uint32_t *)fwdata, 2, 119);
  FWDA_CS_by_SW = Calc_Checksum_FWD((uint32_t *)fwdata, 120, 122);
  
  // CHECKSUM VERIFICATION
  // Step 1 (new)
  Preparation();

      //Preparation of CR 0xC4
      config_c4 = Read_Dword(RC_RAA_RD_RAM, 0xC4);
      config_c4 |= IRQ_EN_TRANS_FNS_mask;
      config_c4 |= IRQ_EN_CHKSUM_FNS_mask;
      Write_Dword(RC_RAA_WR_RAM, 0xC4, config_c4);
      
  // Step 4
  FWU_RNG = Read_Dword(RC_RAA_RD_RAM, SRR_FWU_RNG);
  // Step 5
  FWU_REV = Read_Dword(RC_RAA_RD_RAM, SRR_FWU_REV);
  FWA_REV = Read_Dword(RC_RAA_RD_RAM, SRR_FWA_REV);
  // Step 6
  if ( (Read_Dword(RC_RAA_RD_RAM, 0xEA)&BLD_FNS_mask) != BLD_FNS_mask )
  {
    puts("FW LOCKED");
    puts("Reading the NVRAM is not possible");
    return; //ignore <return;> to show empty NVRAM
  }
  // Step 7
#ifdef UFC_DEVICE_AS6031
  Write_Dword(RC_RAA_WR_RAM, SHR_RC_RLS, 0x50F5B8CA);
#else
  Write_Dword(RC_RAA_WR_RAM, SHR_FW_TRANS_EN, 0x50F5B8CA);
#endif
 
  // Step 13
  Write_Opcode(RC_IF_CLR);  //clear interrupt flag register
  // Step 14
  Write_Dword(RC_RAA_WR_RAM, SHR_RC, 0x00080000);
  // Step 15
  // Check on interrupt FW_TRANS_FNS
  interrupt = 0;
  do {
    interrupt = Read_Dword(RC_RAA_RD_RAM, SRR_IRQ_FLAG);
    interrupt &= FW_TRANS_FNS_mask; //check bit 1
  } while (interrupt != FW_TRANS_FNS_mask);
 
  // Step 16
  Write_Opcode(RC_IF_CLR);  //clear interrupt flag register
  // Step 17
  Write_Dword(RC_RAA_WR_RAM, SHR_RC, 0x00100000);
  // Step 18
  // Check on interrupt FW_TRANS_FNS
  interrupt = 0;
  do {
    interrupt = Read_Dword(RC_RAA_RD_RAM, SRR_IRQ_FLAG);
    interrupt &= FW_TRANS_FNS_mask; //check bit 1
  } while (interrupt != FW_TRANS_FNS_mask);

  // Step 19
  Write_Opcode(RC_IF_CLR);  //clear interrupt flag register
  // Step 20
  Write_Opcode(RC_FW_CHKSUM);
  // Step 21
  // Check on interrupt IRQ_EN_CHKSUM_FNS
  interrupt = 0;
  do {
    interrupt = Read_Dword(RC_RAA_RD_RAM, SRR_IRQ_FLAG);
    interrupt &= CHKSUM_FNS_mask;
  } while (interrupt != CHKSUM_FNS_mask);

  // Step 22-25
int del = 2; /* Note: needed delay and workaround for suitable read data */
OSTimeDly( del,
               OS_OPT_TIME_DLY,
               &idle_err);
  FWDU_CS_by_HW = Read_Dword(RC_RAA_RD_RAM, 0xA8);
  OSTimeDly( del,
                 OS_OPT_TIME_DLY,
                 &idle_err);
  FWDA_CS_by_HW = Read_Dword(RC_RAA_RD_RAM, 0xA9);
  OSTimeDly( del,
                 OS_OPT_TIME_DLY,
                 &idle_err);
  FWCU_CS_by_HW = Read_Dword(RC_RAA_RD_RAM, 0xAA);
  OSTimeDly( del,
                 OS_OPT_TIME_DLY,
                 &idle_err);
  FWCA_CS_by_HW = Read_Dword(RC_RAA_RD_RAM, 0xAB);

  // Step 26
  Write_Opcode(RC_IF_CLR);
  // Step 27
#ifdef UFC_DEVICE_AS6031
  Write_Dword(RC_RAA_WR_RAM, SHR_RC_RLS, 0x00000000);
#else
  Write_Dword(RC_RAA_WR_RAM, SHR_FW_TRANS_EN, 0x00000000);
#endif
  
  // Step xx - Read content from NVRAM
  OSTimeDly( del,
                 OS_OPT_TIME_DLY,
                 &idle_err);
  FWDU_CS_by_NVRAM = Read_Dword(RC_RAA_RD_NVRAM, 0x01); //Firmware Data User, Checksum (0x101)
  OSTimeDly( del,
                 OS_OPT_TIME_DLY,
                 &idle_err);
  FWDA_CS_by_NVRAM = Read_Dword(RC_RAA_RD_NVRAM, 0x7D); //Firmware Data AMS, Checksum  (0x17D)
  OSTimeDly( del,
                 OS_OPT_TIME_DLY,
                 &idle_err);
  FWCU_CS_by_NVRAM = Read_Dword(RC_RAA_RD_NVRAM, 0x00); //Firmware Code User, Checksum (0x100)
  OSTimeDly( del,
                 OS_OPT_TIME_DLY,
                 &idle_err);
  FWCA_CS_by_NVRAM = Read_Dword(RC_RAA_RD_NVRAM, 0x7E); //Firmware Code AMS, Checksum  (0x17E)
}
#endif

/******************************************************************************/
/*                               Print Checksum                               */ 
/******************************************************************************/
/**
  * @brief  This function prints all Checksums.
  * @retval none
  */
void Printf_Checksum(void)
{
  /* print checksums on Terminal I/O */
  printf("\nFirmware User Code - Checksums\n");
  printf(" Calculated by Software\t= 0x%08X\n",   (unsigned int)FWCU_CS_by_SW);
  printf(" Calculated by Hardware\t= 0x%08X\n",   (unsigned int)FWCU_CS_by_HW);
  printf(" Read from NVRAM, 0x100\t= 0x%08X\n\n", (unsigned int)FWCU_CS_by_NVRAM);
  printf(" User FW Revision\t= 0x%08X\n",         (unsigned int)FWU_REV);
  printf(" User FW Range\t\t= 0x%08X\n",          (unsigned int)FWU_RNG);
  
  printf("\nFirmware ams Code - Checksums\n");
  printf(" Calculated by Hardware\t= 0x%08X\n",   (unsigned int)FWCA_CS_by_HW);
  printf(" Read from NVRAM, 0x17E\t= 0x%08X\n\n", (unsigned int)FWCA_CS_by_NVRAM);
  printf(" ams FW Revision\t= 0x%08X\n",          (unsigned int)FWA_REV);
  
  printf("\nFirmware Data - Checksums\n");
  printf(" FWD User, cell# 2-119\n");
  printf(" Calculated by Software\t= 0x%08X\n",   (unsigned int)FWDU_CS_by_SW);
  printf(" Calculated by Hardware\t= 0x%08X\n",   (unsigned int)FWDU_CS_by_HW);
  printf(" Read from NVRAM, 0x101\t= 0x%08X\n\n", (unsigned int)FWDU_CS_by_NVRAM);
  printf(" FWD ams, cell# 120-122\n");
  printf(" Calculated by Software\t= 0x%08X\n",   (unsigned int)FWDA_CS_by_SW);
  printf(" Calculated by Hardware\t= 0x%08X\n",   (unsigned int)FWDA_CS_by_HW);
  printf(" Read from NVRAM, 0x17D\t= 0x%08X\n",   (unsigned int)FWDA_CS_by_NVRAM);
  
  printf("\n...END\n\n");
}

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*                             Read System Status                             */ 
/******************************************************************************/
/**
  * @brief  This function reads System Status.
  * @retval one byte
  */
int System_Status(void)
{
  /* Timeout duration in millisecond [ms] */
  uint8_t timeout = 10; 
  
  uint8_t spiTX[1];
  uint8_t spiRX[1];

  spiTX[0] = RC_RD_STATUS; //Opcode

  /* 1. Put SSN low - Activate */
  Set_SSN(LOW);
  
  /* 2. Transmit opcode */
  SPIDRV_MTransmit  (SPI_HANDLE,spiTX,1,callback2 );

  
  /* 3. Read one byte */
  SPIDRV_MReceive  (SPI_HANDLE,spiRX,1,callback2 );

  /* 4. Put SSN high - Deactivate */
  Set_SSN(HIGH);

  return spiRX[0];
}
#endif

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*                             Print System Status                            */ 
/******************************************************************************/
/**
  * @brief  This function prints the read System Status.
  * @retval none
  */
void Print_System_Status(void)
{
  uint8_t spiRX[1];
  
  spiRX[0] = System_Status();
  
  puts("Reading of System Status");
  
  /* provide Status if not zero */
  if ((spiRX[0] & 0xE3) != 0)
  {
    printf("SYS_STATUS = 0x%02X\n", spiRX[0]);
    if ((spiRX[0] & 0x01) != 0) printf(" [Bit0] -> RAA_BUSY (internal processes ongoing)\n");
    if ((spiRX[0] & 0x02) != 0) printf(" [Bit1] -> TSQ_BUSY_PRED (remaining idle time prediction)\n");
    if ((spiRX[0] & 0x20) != 0) printf(" [Bit5] -> COM_FAIL (Communication Failed)\n");
    if ((spiRX[0] & 0x40) != 0) printf(" [Bit6] -> RST_FLAG (clear RST_FLAG after reading)\n");
    if ((spiRX[0] & 0x80) != 0) printf(" [Bit7] -> ERR_FLAG (only one bit in 0xE1 is set)\n");
  }
  
  /* provide Status anytime */
  printf(" [Bit3:2] -> MT_REQ_CTR = %u\n", convert_gray2dec((spiRX[0]&0x0C)>>2) );
  
  if ((spiRX[0]&0x10)!=0) {
    printf(" [Bit4] -> MCT_STATE = ON (Status of Measure Cycle Timer)\n");
  } else {
    printf(" [Bit4] -> MCT_STATE = OFF (Status of Measure Cycle Timer)\n");
  }

}
#endif

#ifdef UFC_DEVICE_AS6031
/******************************************************************************/
/*             Polling System Status within delay with steps of 1ms           */ 
/******************************************************************************/
/**
  * @brief  This function polls the System Status within delay with step of 1ms
  *             and prints the accumulated System Status.
  * @param  Delay 32-bit value sets delay of multiple of 1ms
  * @retval none
  */
void SYS_Status_Delay(uint32_t Delay)
{
  uint32_t tickstart = sl_sleeptimer_get_tick_count64();
  uint32_t wait = Delay;
  uint8_t ctr_new = 0;
  uint8_t ctr_old = 0;
  
  int sys_start = 0;

  /* Add a period to guaranty minimum wait */
  if (wait < 0xFFFFFFFFU)
  {
    wait += (uint32_t)(1);
  }
  
  puts("Reading of accumulated System Status");
  printf(" [Bit3:2] -> MT_REQ_CTR = ");
  while((sl_sleeptimer_get_tick_count64() - tickstart) < wait)
  {
    /* Accumulated System Status*/
    sys_start |= System_Status();
    
    ctr_new = convert_gray2dec( (sys_start & 0x0C)>>2);
    
    if (ctr_new == ctr_old)
    { } else
    {
      /* show only changes */
      printf("%u", ctr_new);
    }
    ctr_old = ctr_new;
    sys_start &= 0xF3;
  }
  printf("\n");

  /* provide Status if not zero */
  if (sys_start!=0) 
  {
    printf("Accumulated SYS_STATUS = 0x%02X\n", sys_start);
    if ((sys_start&0x01)!=0) printf(" [Bit0] -> RAA_BUSY (internal processes ongoing)\n");
    if ((sys_start&0x02)!=0) printf(" [Bit1] -> TSQ_BUSY_PRED (remaining idle time prediction)\n");
    if ((sys_start&0x20)!=0) printf(" [Bit5] -> COM_FAIL (Communication Failed)\n");
    if ((sys_start&0x40)!=0) printf(" [Bit6] -> RST_FLAG (clear RST_FLAG after reading)\n");
    if ((sys_start&0x80)!=0) printf(" [Bit7] -> ERR_FLAG (only one bit in 0xE1 is set)\n");
  }
  
  /* provide Status anytime */
  if ((sys_start&0x10)!=0) {
    printf(" [Bit4] -> MCT_STATE = ON (Status of Measure Cycle Timer)\n");
  } else {
    printf(" [Bit4] -> MCT_STATE = OFF (Status of Measure Cycle Timer)\n");
  }
  
}
#endif

/******************************************************************************/
/*                              Update Timestamp                              */ 
/******************************************************************************/
/**
  * @brief  This function updates the Timestamp into defined variables:
  *         TS_HOUR, TS_MIN and TS_SEC
  *         Example:
  *             Update_TimeStamp();
  *             printf("Current TS Timer Status");
  *             printf(" = %02u:%02u:%02u \n", TS_HOUR, TS_MIN, TS_SEC);
  *         The time stamp can be updated automatically every second. But it is
  *         possible to trigger an update as well as to clear the content, both
  *         by setting excecutables in the special handling registers.

CR_CPM (Clock & Power Management) Addr. 0xC5
TSV_UPD_MODE[bit 22] - Time stamp update mode
0: updated by TSV_UPD in SHR_EXC
1: automatically updated every second, use this setting

SHR_EXC(Executables) Addr. 0xDD
TSV_UPD[bit 4] - Time stamp value update
0: No action
1: Update time stamp value from time stamp counter

TSC_CLR[bit 3] - Time stamp counter clear
0: No action
1: Clears time stamp counter

  * @param  none
  * @retval none
  */
void Update_TimeStamp(void)
{
  //#define _DEBUGGGING_FUNCTION
  
  uint32_t TSV_UPD_MODE_content;
  uint32_t MCT_RLS_content;
  
  MCT_RLS_content = Read_Dword_Bits(RC_RAA_RD_RAM, 0xEA, 8, 8);
  TSV_UPD_MODE_content = Read_Dword_Bits(RC_RAA_RD_RAM, 0xC5, 22, 22);

#ifdef _DEBUGGGING_FUNCTION
  printf("MCT_RLS = %08X\n", MCT_RLS_content);
  if (MCT_RLS_content) puts("MCT_RLS = ON");
  else puts("MCT_RLS = OFF");
  
  printf("TSV_UPD_MODE = %08X\n", TSV_UPD_MODE_content);
  if (TSV_UPD_MODE_content) {
    puts("TSV_UPD_MODE = 1: automatically updated every measure cycle trigger");
  }
  else puts("TSV_UPD_MODE = 0: updated by TSV_UPD in SHR_EXC");
#endif
  
  /* TSV_UPD_MODE = 1 && MCT_RLS = 1 */
  /* nothing to do, ... automatically updated */

  /* TSV_UPD_MODE = 1 && MCT_RLS = 0 */
  if (TSV_UPD_MODE_content && !MCT_RLS_content) {
    /* Clear TSV_UPD_MODE */
    Update_Dword_Bits(RC_RAA_RD_RAM, 0xC5, RC_RAA_WR_RAM, 22, 22, 0);
    /* Set TSV_UPD in SHR_EXC */
    Set_Bit_No(RC_RAA_WR_RAM, 0xDD, 4);
  }

  /* TSV_UPD_MODE = 0 */
  if (!TSV_UPD_MODE_content) {
    /* Set TSV_UPD in SHR_EXC */
    Set_Bit_No(RC_RAA_WR_RAM, 0xDD, 4);
  }
  
  uint32_t timestamp = 0;

  /* Timestamp hours, 18-bit values, 1 LSB: 1h */
  timestamp = Read_Dword(RC_RAA_RD_RAM, SRR_TSV_HOUR);
    /* TS_HOUR[17:0] */
  TS_HOUR = timestamp & 0x0003FFFF;

  /* Timestamp minutes, 8-bit values, 1 LSB: 1min, range 1 to 59 */
  timestamp = Read_Dword(RC_RAA_RD_RAM, SRR_TSV_MIN_SEC);
  /* TS_MIN[15:8] */
  TS_MIN = (timestamp & 0xFF00)>>8;
  /* TS_SEC[7:0] */
  TS_SEC = timestamp & 0xFF;
  
  #undef _DEBUGGGING_FUNCTION
}

/******************************************************************************/
/*                               Print Timestamp                              */
/******************************************************************************/
/**
  * @brief  This function updates and prints the Timestamp on TERMINAL I/O
  * @retval none
  */
void Printf_TimeStamp(void)
{
  printf("Current TS Timer Status");
  printf(" = %02u:%02u:%02u \n", (unsigned int)TS_HOUR, (unsigned int)TS_MIN, (unsigned int)TS_SEC);
}
/*
void Printf_TimeStamp2(uint32_t *hour, uint32_t *min, uint32_t *sec)
{
  Update_TimeStamp(hour, min, sec);

  printf("Current TS Timer Status");
  printf(" = %02u:%02u:%02u \n", (unsigned int)*hour, (unsigned int)*min, (unsigned int)*sec);
}
*/

/******************************************************************************/
/*                              Print VCC Voltage                             */
/******************************************************************************/
/**
  * @brief  This function updates and prints the VCC Voltage on TERMINAL I/O
  * @retval none
  */
void Printf_VCC_VAL(void)
{
	/* VCC_VAL[5:0]: Measured value of VCC voltage
	 *  1 LSB: 25 mV
	 *  VCC_VAL = 0: 2.13 V
	 *  VCC_VAL = 63: 3.70 V
	 *   */
	float min = 2.13;
	float LSB =0.025;

	VCC_VAL = Read_Dword_Bits(RC_RAA_RD_RAM, SRR_VCC_VAL, 5, 0);

	printf("Current VCC_VAL Value");
	printf(" = %1.2f \n", min + ( (unsigned int)VCC_VAL * LSB ));
}

/******************************************************************************/
/*                              Put UFC Into Idle                             */
/******************************************************************************/
/**
  * @brief  This function puts UFC into idle phase and stops the measurement.
  * @retval none
  */
void Put_UFC_Into_Idle(void)
{
	Write_Opcode(RC_SYS_RST); //Reset UFC completely
	for(int i=0;i<1000;i++){

	}
	Write_Dword(RC_RAA_WR_RAM, CR_WD_DIS, WD_DIS_CODE); //STEP 1 - Disable Watchdog by writing code to CR_WD_DIS
	Write_Opcode(RC_MCT_OFF);
}

/******************************************************************************/
/*                            Calculates HS_CLOCK                             */
/******************************************************************************/
/**
  * @brief  This function reads HCC_VAL and calculates real HS_CLOCK.
  * @param  time_unit 32-bit value, corresponds to the time unit of the
  * 		calculated High Speed Clock value
  * 		E.g.: 'time_unit' = 1e-9 corresponds to 'ns'
  * @retval Real High Speed Clock
  */
float Calc_HighSpeedClock(float time_unit)
{
	/* local parameter */
	uint32_t RAWvalue = 0;
	float FLOATValue = 0;
	float CalFactor = 0;
	float CalHSClk = 0;

	RAWvalue = Read_Dword(RC_RAA_RD_RAM, SRR_HCC_VAL);
	/* Calculating of Calibration Factor */
	FLOATValue = RAWvalue / 65536;       /* = 2^16 */
	FLOATValue *= T_REF;
	CalFactor = (4 * T_LS_CLK) / FLOATValue;
	/* Output */
	CalHSClk = (T_REF * CalFactor) / time_unit;

	return CalHSClk;
}

/******************************************************************************/
/*                         Calculates Amplitude in mV                         */
/******************************************************************************/
/**
  * @brief  This function calculates amplitude of Rx in mV.
  * @param  AM_address 32-bit value, Ultrasonic amplitude value, direction
  * @param  AMC_VH 32-bit value, Ultrasonic amplitude calibration value, high
  * @param  AMC_VL 32-bit value, Ultrasonic amplitude calibration value, low
  * @retval Measured Amplitude in mV
  */
float Calc_Amplitude(uint32_t AM_address, uint32_t AMC_VH, uint32_t AMC_VL)
{
	/* local parameter */
	uint32_t RAWValue = 0;
	float AMC_gradient = 0;
	float AMC_offset = 0;
	float FLOATValue = 0;

	RAWValue = Read_Dword(RC_RAA_RD_RAM, AM_address);
	AMC_gradient = 350 / (float)(AMC_VH - AMC_VL);
	AMC_offset = ((2 * AMC_VL) - AMC_VH) * AMC_gradient;

	FLOATValue = (AMC_gradient * RAWValue) - AMC_offset;

	return FLOATValue;
}

/******************************************************************************/
/*                    Calculates Time Of Flight in seconds                    */
/******************************************************************************/
/**
  * @brief  This function calculates time of flight of Rx.
  * @param  TOF_address 32-bit value, Ultrasonic TOF value, direction
  * @retval Measured Time Of Flight in seconds
  */
float Calc_TimeOfFlight(uint32_t TOF_address)
{
	/* local parameter */
	uint32_t RAWValue = 0;
	float FLOATValue = 0;

	RAWValue = Read_Dword(RC_RAA_RD_RAM, TOF_address);
	/* Calculation of Time of Flight */
	FLOATValue = Two_s_Complement_Conversion(RAWValue, 16, T_REF);

	return FLOATValue;
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
