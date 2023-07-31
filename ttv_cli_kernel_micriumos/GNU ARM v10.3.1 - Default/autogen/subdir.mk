################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../autogen/sl_board_default_init.c \
../autogen/sl_cli_command_table.c \
../autogen/sl_cli_instances.c \
../autogen/sl_device_init_clocks.c \
../autogen/sl_event_handler.c \
../autogen/sl_iostream_handles.c \
../autogen/sl_iostream_init_usart_instances.c \
../autogen/sl_simple_led_instances.c \
../autogen/sl_spidrv_init.c \
../autogen/sl_uartdrv_init.c \
../autogen/sli_cli_hooks.c 

OBJS += \
./autogen/sl_board_default_init.o \
./autogen/sl_cli_command_table.o \
./autogen/sl_cli_instances.o \
./autogen/sl_device_init_clocks.o \
./autogen/sl_event_handler.o \
./autogen/sl_iostream_handles.o \
./autogen/sl_iostream_init_usart_instances.o \
./autogen/sl_simple_led_instances.o \
./autogen/sl_spidrv_init.o \
./autogen/sl_uartdrv_init.o \
./autogen/sli_cli_hooks.o 

C_DEPS += \
./autogen/sl_board_default_init.d \
./autogen/sl_cli_command_table.d \
./autogen/sl_cli_instances.d \
./autogen/sl_device_init_clocks.d \
./autogen/sl_event_handler.d \
./autogen/sl_iostream_handles.d \
./autogen/sl_iostream_init_usart_instances.d \
./autogen/sl_simple_led_instances.d \
./autogen/sl_spidrv_init.d \
./autogen/sl_uartdrv_init.d \
./autogen/sli_cli_hooks.d 


# Each subdirectory must supply rules for building sources it contributes
autogen/sl_board_default_init.o: ../autogen/sl_board_default_init.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_board_default_init.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_cli_command_table.o: ../autogen/sl_cli_command_table.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_cli_command_table.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_cli_instances.o: ../autogen/sl_cli_instances.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_cli_instances.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_device_init_clocks.o: ../autogen/sl_device_init_clocks.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_device_init_clocks.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_event_handler.o: ../autogen/sl_event_handler.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_event_handler.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_iostream_handles.o: ../autogen/sl_iostream_handles.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_iostream_handles.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_iostream_init_usart_instances.o: ../autogen/sl_iostream_init_usart_instances.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_iostream_init_usart_instances.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_simple_led_instances.o: ../autogen/sl_simple_led_instances.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_simple_led_instances.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_spidrv_init.o: ../autogen/sl_spidrv_init.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_spidrv_init.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_uartdrv_init.o: ../autogen/sl_uartdrv_init.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_uartdrv_init.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sli_cli_hooks.o: ../autogen/sli_cli_hooks.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG11B820F2048GL192=1' '-DSL_BOARD_NAME="BRD2204A"' '-DSL_BOARD_REV="B07"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\config" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos\autogen" -I"C:\Users\runhu\SimplicityStudio\workspace_TTV\ttv_cli_kernel_micriumos" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG11B/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/cli/src" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/common/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/cpu/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/ports/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/source" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/micrium_os/kernel/include" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/spidrv/inc" -I"C:/Users/runhu/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sli_cli_hooks.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

