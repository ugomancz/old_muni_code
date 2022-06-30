################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mk66f18.c 

OBJS += \
./startup/startup_mk66f18.o 

C_DEPS += \
./startup/startup_mk66f18.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/disco_button/board" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/disco_button/source" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/disco_button" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/disco_button/drivers" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/disco_button/device" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/disco_button/CMSIS" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/disco_button/component/uart" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/disco_button/utilities" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/disco_button/component/serial_manager" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/disco_button/component/lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


