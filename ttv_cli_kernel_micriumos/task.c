#include "cli.h"
#include "os.h"
#include "task.h"
#include "user_tools.h"
#include "user_spi_interface.h"
#include "user_cfg.h"

#include "user_UFC_cmd.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_device.h"
#include "em_chip.h"
#ifndef TERMINAL_TASK_STACK_SIZE
#define TERMINAL_TASK_STACK_SIZE      256
#endif

#ifndef TERMINAL_TASK_PRIO
#define TERMINAL_TASK_PRIO            20
#endif

#define UFC_DEVICE_AS6031
volatile uint32_t My_INTN_Counter = 0;


volatile uint8_t My_INTN_State = 1; /* low active */

// For Debugging
volatile uint8_t My_Chip_initialized = 0;
volatile uint8_t My_Chip_config_1 = 0;
volatile uint8_t My_Chip_config_2 = 0;
volatile uint8_t My_Chip_config_3 = 0;
volatile uint8_t My_Chip_idle_state = 0;

//char My_Configuration[20] = {'\0'}; //null character '\0' at the end by default.
// char     My_Config_1[20]  = "GP30YA-F01_ST_NS";
// char     My_Config_2[20]  = "AS6031_ST_NS";
// char     My_Config_3[20]  = "AS6040_ST_NS";

volatile uint32_t My_Cycle_A_Counter = 0;
volatile uint32_t My_Cycle_B_Counter = 0;
volatile uint32_t My_Loop_Pass_Counter = 0;

volatile uint32_t My_ERROR_Counter = 0;
volatile uint32_t My_UP_zero = 0;
volatile uint32_t My_DOWN_zero = 0;

volatile uint32_t My_Min_Value_A = 0xFFFFFFFF, My_Max_Value_A = 0,
    My_Min_Value_B = 0xFFFFFFFF, My_Max_Value_B = 0;
volatile uint32_t My_Too_Less_Time = 0;

volatile uint8_t My_New_Configuration = 2;
volatile uint8_t My_New_FHL = 0;
volatile float My_New_FHL_mV = 0;
volatile float My_Set_FHL_mV = 0;

volatile uint8_t MyMode = 1; /* default */

uint32_t SRR_IRQ_FLAG_content =0; //Interrupt Flags
uint32_t SRR_ERR_FLAG_content =0; //Error Flags
uint32_t  SRR_FEP_STF_content =0; //Frontend Processing Status Flags
uint32_t  SRR_TS_TIME_content =0;

// Post Processing - Time Conversion Mode (MyMode = 1)
uint32_t MyRAWValueUP;
uint32_t MyRAWValueDOWN;
uint32_t MyRAWAMCVH;
uint32_t MyRAWAMCVL;
uint32_t MyRAWPWUP;
uint32_t MyRAWPWDOWN;

float MyTOFSumAvgUP;
float MyTOFSumAvgDOWN;
float MyDiffTOFSumAvg;
float MyRealAMUP;
float MyRealAMDOWN;
float MyRealPWUP;
float MyRealPWDOWN;
float MyRealHSClk;

// Scaling
float MyRealHSClk_ns;
float MyTOFSumAvgUP_ns;
float MyTOFSumAvgDOWN_ns;
float MyDiffTOFSumAvg_ps;

// Post Processing - Flow Meter Mode (MyMode = 2)
float MyFlow;
float MyTheta;


static OS_TCB tcb;
static CPU_STK stack[TERMINAL_TASK_STACK_SIZE];
RTOS_ERR err;
void My_Init_State(void) {
  /* reset counter */
  My_INTN_Counter = 0;
  My_Cycle_A_Counter = 0;
  My_Cycle_B_Counter = 0;
  My_Loop_Pass_Counter = 0;
  My_ERROR_Counter = 0;
  My_UP_zero = 0;
  My_DOWN_zero = 0;
  My_Too_Less_Time = 0;

  /* expand range */
  My_Min_Value_A = 0xFFFFFFFF;
  My_Max_Value_A = 0;
  My_Min_Value_B = 0xFFFFFFFF;
  My_Max_Value_B = 0;

  My_New_Configuration = 0;

  My_Chip_initialized = 1;
}
void My_Time_Conversion_Mode(void) {
  /* Time Conversion Mode */
  /* Cylce A = ~ 370 µs @SPI = 2.5 MHz*/
  /* Cylce B = ~ 160 µs @SPI = 2.5 MHz*/

  /* STEP 2 - Read SRR_ERR_FLAG to check if any error
   *  occurred during last measurement cycle */
  SRR_ERR_FLAG_content = Read_Dword(RC_RAA_RD_RAM, SRR_ERR_FLAG);
  /* STEP 3 - Read SRR_FEP_STF to check which
   * measurement has been updated in last measure cycle */
  SRR_FEP_STF_content = Read_Dword(RC_RAA_RD_RAM, SRR_FEP_STF);

  if (SRR_ERR_FLAG_content > 0) {
    //Error Handling with simplified query

    /* Chip has to be reinitialized */
    printf("Error Reached! FLAG: %d..\n",SRR_ERR_FLAG_content);
    My_Chip_initialized = 0;
    My_Chip_idle_state = 0;
    /* Skipping Post Processing
     * Jump to Step 5 */

  } else {
    //Post Processing without any Error

    //only if enough time, more than 1 ms
    if (SRR_TS_TIME_content > 1) {
      //determine min/max value for debugging Cycle A
      if (SRR_TS_TIME_content > My_Max_Value_A) {
        My_Max_Value_A = SRR_TS_TIME_content;
      }
      if (SRR_TS_TIME_content < My_Min_Value_A) {
        My_Min_Value_A = SRR_TS_TIME_content;
      }

      /* STEP 4 - read the measurement results
       * out of the frontend data buffer */

      //Post Processing Cycle A
      if (SRR_FEP_STF_content
          & (US_AMC_UPD_mask | US_AM_UPD_mask | US_TOF_EDGE_mask |
          US_TOF_UPD_mask | US_D_UPD_mask | US_U_UPD_mask)) {
        My_Cycle_A_Counter += 1; //counts every call

        if (SRR_FEP_STF_content & (US_AMC_UPD_mask)) {
          /* Updating of Ultrasonic amplitude calibration values */
          MyRAWAMCVH = Read_Dword(RC_RAA_RD_RAM, FDB_US_AMC_VH);
          MyRAWAMCVL = Read_Dword(RC_RAA_RD_RAM, FDB_US_AMC_VL);
        }

        if (SRR_FEP_STF_content & (US_AM_UPD_mask)) {
          /* If amplitude calibration values = ZERO
           * Reloading amplitude calibration values */
          if (MyRAWAMCVH == 0 || MyRAWAMCVL == 0) {
            MyRAWAMCVH = Read_Dword(RC_RAA_RD_RAM, FDB_US_AMC_VH);
            MyRAWAMCVL = Read_Dword(RC_RAA_RD_RAM, FDB_US_AMC_VL);
          }

          /* If amplitude calibration values are available
           * Updating amplitude values */
          if (MyRAWAMCVH != 0 && MyRAWAMCVL != 0) {
            MyRealAMUP = Calc_Amplitude(FDB_US_AM_U, MyRAWAMCVH,
                MyRAWAMCVL);
            MyRealAMDOWN = Calc_Amplitude(FDB_US_AM_D, MyRAWAMCVH,
                MyRAWAMCVL);
          }
        }

        if (SRR_FEP_STF_content
            & (US_TOF_UPD_mask | US_D_UPD_mask | US_U_UPD_mask)) {
          /* Updating TOF Values */
          MyTOFSumAvgUP = Calc_TimeOfFlight(FDB_US_TOF_ADD_ALL_U)
              / TOF_HIT_SUM_NO;
          MyTOFSumAvgDOWN = Calc_TimeOfFlight(FDB_US_TOF_ADD_ALL_D)
              / TOF_HIT_SUM_NO;

          if (MyTOFSumAvgUP == 0) {
            My_UP_zero++;
          }
          if (MyTOFSumAvgDOWN == 0) {
            My_DOWN_zero++;
          }

          /* Updating Pulse Width Ratio */
          MyRAWPWUP = Read_Dword(RC_RAA_RD_RAM, FDB_US_PW_U);
          MyRAWPWDOWN = Read_Dword(RC_RAA_RD_RAM, FDB_US_PW_D);

          //post processing and calculation
          MyDiffTOFSumAvg = (MyTOFSumAvgDOWN - MyTOFSumAvgUP);

          MyRealPWUP = MyRAWPWUP;
          MyRealPWUP /= (1 << 7);
          MyRealPWDOWN = MyRAWPWDOWN;
          MyRealPWDOWN /= (1 << 7);

          //scaling
          MyTOFSumAvgUP_ns = MyTOFSumAvgUP / 1e-9;
          MyTOFSumAvgDOWN_ns = MyTOFSumAvgDOWN / 1e-9;
          MyDiffTOFSumAvg_ps = MyDiffTOFSumAvg / 1e-12;
        }

      }

      //determine min/max value for debugging Cycle B
      if (SRR_TS_TIME_content > My_Max_Value_B) {
        My_Max_Value_B = SRR_TS_TIME_content;
      }
      if (SRR_TS_TIME_content < My_Min_Value_B) {
        My_Min_Value_B = SRR_TS_TIME_content;
      }

      //Post Processing Cycle B
      if (SRR_FEP_STF_content
          & (TPM_ST_mask | TM_MODE_mask | TM_UPD_mask | HCC_UPD_mask)) {

        My_Cycle_B_Counter += 1; //counts every call

        //if flag then reading of...
        if (SRR_FEP_STF_content & (HCC_UPD_mask)) {
          MyRealHSClk_ns = Calc_HighSpeedClock(1e-9);
        }

      }

    } else {
      //there is not enough time
      My_Too_Less_Time += 1;
      printf("Too Less Time!!!!\n");
    }
    //Print out the data in 8 digit signed 2's complement Hex.
    printf("TOF: %d ps\r\n", (int)MyDiffTOFSumAvg_ps);
    /* STEP 5 - Clear interrupt flag, error flag & frontend status
     * flag register by writing code to SHR_EXC */
    Write_Dword(RC_RAA_WR_RAM, SHR_EXC,
        (FES_CLR_mask | EF_CLR_mask | IF_CLR_mask));
    My_INTN_State = 1;

  } //End of Post Processing
}
void task_init (){
  OSTaskCreate (&tcb, "iostream terminal task", terminal_task,
                DEF_NULL,
                TERMINAL_TASK_PRIO, &stack[0], (TERMINAL_TASK_STACK_SIZE / 10u),
                TERMINAL_TASK_STACK_SIZE,
                0u, 0u,
                DEF_NULL,
                (OS_OPT_TASK_STK_CLR ), &err);
  EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));
}
#ifndef __even_H
#define __even_H
///**
void gpioCallback12(void)
{
  // Clear all even pin interrupt flags
  My_INTN_Counter += 1;
  My_INTN_State = 0;
  GPIO_IntClear(1 << 12);
}//**/
#endif
void init_intn(){


  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(gpioPortE,13,gpioModePushPull,0);
  GPIO_PinModeSet(gpioPortA,12,gpioModeInput,0);
  GPIO_ExtIntConfig(gpioPortA, 12, 12, true, false, true); // gpioPortA, pin 12, rising edge interrupt
   GPIOINT_Init();
   // Register callback functions and enable interrupts
   GPIOINT_CallbackRegister(12, gpioCallback12);
   GPIO_IntEnable(1<<12);

}

void terminal_task(){
  init_intn();
  while (1) {
      /* USER CODE END WHILE */
      //spi testing
      /*uint8_t timeout = 10; //Timeout duration in millisecond [ms]
       uint8_t spiTX[3];
       uint8_t spiRX[3];
       spiTX[0]=0xAA;
       spiTX[1]=0xBB;
       spiTX[2]=0xCC;
       Set_SSN(LOW);
       HAL_SPI_Receive(&hspi1, spiRX, 3, timeout); //gap between read bytes 1us
       HAL_SPI_Transmit(&hspi1, spiTX, 3, timeout);//possibly remove this line of code
       Set_SSN(HIGH);*/

      My_Loop_Pass_Counter += 1; //counts every loop



      //unix timestamp calculation


      //INTN checking
      if ((My_INTN_State == 0) && (My_Chip_initialized == 1)) {
        /* Step 1 - Check on Interrupt pin */
        /* Step 1a - Optionally read current task sequencer time */
        SRR_TS_TIME_content = Read_Dword(RC_RAA_RD_RAM, SRR_TS_TIME);

        switch (MyMode) {
        case 1:
          My_Time_Conversion_Mode();
          break;
        default:
          MyMode = 1;
          break;
        }

        /* Update Configuration */
        if (My_New_FHL_mV > 0) {
          /* Update System Handling Register
           * SHR_FHL_U (First Hit Level Up) 0x0DA
           * SHR_FHL_D (First Hit Level Down) 0x0DB
           */
          My_New_FHL = My_New_FHL_mV / 0.88;
          Write_Dword(RC_RAA_WR_RAM, SHR_ZCD_FHL_U, My_New_FHL);
          Write_Dword(RC_RAA_WR_RAM, SHR_ZCD_FHL_D, My_New_FHL);

          My_Set_FHL_mV = My_New_FHL_mV;
          My_New_FHL_mV = 0;
        }
      } //End of (My_INTN_State == true) query

      /* Reload Configuration */
      if (My_New_Configuration > 0) {
        printf("reload...\n");
        My_Chip_initialized = 0;
        My_Chip_config_1 = 0;
        My_Chip_config_2 = 0;
        My_Chip_config_3 = 0;

        Put_UFC_Into_Idle();
        My_Chip_idle_state = 1;

        if (My_New_Configuration != 99) {
          switch (My_New_Configuration) {
          case 1:
            //GP30YA-F01_ST_NS
            //strcpy(My_Configuration, "GP30YA-F01_ST_NS");
            My_Chip_config_1 = 1;
            break;
          case 2:
            //AS6031_ST_NS
            //strcpy(My_Configuration, "AS6031_ST_NS");
            My_Chip_config_2 = 1;
            My_Write_CFG_AS6031_1MHz_SpoolPiece();
            OSTimeDly( 20,
                           OS_OPT_TIME_DLY,
                           &err);
            break;
          case 3:
            //AS6040_ST_NS
            //strcpy(My_Configuration, "AS6040_ST_NS");
            My_Chip_config_3 = 1;
            My_Write_CFG_AS6040_500kHz_SpoolPiece();
            Write_Opcode(RC_SYS_INIT); //Charge pump is uploading to CHP_HV_SEL
            OSTimeDly( 20,
                           OS_OPT_TIME_DLY,
                           &err);
            break;
          default:
            break;
          }
          My_Set_FHL_mV = Read_Dword(RC_RAA_RD_RAM, SHR_ZCD_FHL_U);

          My_Set_FHL_mV *= 0.88;
          printf("My_Set_FHL_mV:%f\n",My_Set_FHL_mV);
          Write_Opcode(RC_MCT_ON); //RC_MCT_ON
          //Write_Opcode(RC_IF_CLR);
          My_Chip_idle_state = 0;
        }

        My_Init_State();

        //With any ERROR
        //Initialisation of DUT will be cleared
        printf("Init state Error: %d\n",Read_Dword(RC_RAA_RD_RAM, SRR_ERR_FLAG));
        if (Read_Dword(RC_RAA_RD_RAM, SRR_ERR_FLAG)) {
          printf("Error Initializing the board. Please restart the program. \n");
          My_Chip_initialized = 0;
        }

      }

    } //End of while loop

}



