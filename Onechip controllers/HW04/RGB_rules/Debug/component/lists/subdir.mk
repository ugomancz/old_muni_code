################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/lists/generic_list.c 

OBJS += \
./component/lists/generic_list.o 

C_DEPS += \
./component/lists/generic_list.d 


# Each subdirectory must supply rules for building sources it contributes
component/lists/%.o: ../component/lists/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/RGB_rules/board" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/RGB_rules/source" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/RGB_rules" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/RGB_rules/drivers" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/RGB_rules/device" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/RGB_rules/CMSIS" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/RGB_rules/component/uart" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/RGB_rules/utilities" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/RGB_rules/component/serial_manager" -I"/home/xkostik/Documents/MCUXpresso_11.2.0_4120/workspace/RGB_rules/component/lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


