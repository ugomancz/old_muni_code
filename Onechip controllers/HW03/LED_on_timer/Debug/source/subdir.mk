################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LED_on_timer.c \
../source/semihost_hardfault.c 

OBJS += \
./source/LED_on_timer.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/LED_on_timer.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/LED_on_timer/board" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/LED_on_timer/source" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/LED_on_timer" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/LED_on_timer/drivers" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/LED_on_timer/device" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/LED_on_timer/CMSIS" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/LED_on_timer/component/uart" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/LED_on_timer/utilities" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/LED_on_timer/component/serial_manager" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/LED_on_timer/component/lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


