################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/boards/board.c \
../board/boards/clock_config.c \
../board/boards/peripherals.c \
../board/boards/pin_mux.c 

OBJS += \
./board/boards/board.o \
./board/boards/clock_config.o \
./board/boards/peripherals.o \
./board/boards/pin_mux.o 

C_DEPS += \
./board/boards/board.d \
./board/boards/clock_config.d \
./board/boards/peripherals.d \
./board/boards/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/boards/%.o: ../board/boards/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"../board" -I"../source" -I"../" -I"../drivers" -I"../device" -I"../CMSIS" -I"../component/serial_manager" -I"../component/lists" -I"../component/uart" -I"../utilities" -I"../board/boards" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


