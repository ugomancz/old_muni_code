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
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_K66F -DFREEDOM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -I"/home/xkostik/Documents/pv198/frdm_k66f_LCD_1602-Template/drivers" -I"/home/xkostik/Documents/pv198/frdm_k66f_LCD_1602-Template/component/uart" -I"/home/xkostik/Documents/pv198/frdm_k66f_LCD_1602-Template/component/serial_manager" -I"/home/xkostik/Documents/pv198/frdm_k66f_LCD_1602-Template/component/lists" -I"/home/xkostik/Documents/pv198/frdm_k66f_LCD_1602-Template/CMSIS" -I"/home/xkostik/Documents/pv198/frdm_k66f_LCD_1602-Template/utilities" -I"/home/xkostik/Documents/pv198/frdm_k66f_LCD_1602-Template/device" -I../CMSIS -I../component/uart -I../device -I../drivers -I../utilities -I../component/serial_manager -I../component/lists -I../board -I../source -I../ -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


