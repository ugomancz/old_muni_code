################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/port/enet_ethernetif.c \
../lwip/port/enet_ethernetif_kinetis.c \
../lwip/port/sys_arch.c 

OBJS += \
./lwip/port/enet_ethernetif.o \
./lwip/port/enet_ethernetif_kinetis.o \
./lwip/port/sys_arch.o 

C_DEPS += \
./lwip/port/enet_ethernetif.d \
./lwip/port/enet_ethernetif_kinetis.d \
./lwip/port/sys_arch.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/port/%.o: ../lwip/port/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFRDM_K66F -DFREEDOM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/utilities" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/device" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/drivers" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/component/serial_manager" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/board" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/CMSIS" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/component/uart" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/component/lists" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/utilities" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/device" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/drivers" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/component/serial_manager" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/board" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/CMSIS" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/component/uart" -I"/home/xkostik/Documents/pv198/K66F-UDP_SEND-Template/component/lists" -I../device -I../CMSIS -I../lwip/contrib/apps/udpecho_raw -I../component/serial_manager -I../drivers -I../component/uart -I../lwip/port/arch -I../lwip/src/include/compat/posix/arpa -I../lwip/src/include/compat/posix/net -I../lwip/src/include/compat/posix -I../lwip/src/include/compat/posix/sys -I../lwip/src/include/compat/stdc -I../lwip/src/include/lwip -I../lwip/src/include/lwip/priv -I../lwip/src/include/lwip/prot -I../lwip/src/include/netif -I../lwip/src/include/netif/ppp -I../lwip/src/include/netif/ppp/polarssl -I../board -I../source -I../lwip/port -I../component/lists -I../utilities -I../lwip/src -I../lwip/src/include -I../ -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


