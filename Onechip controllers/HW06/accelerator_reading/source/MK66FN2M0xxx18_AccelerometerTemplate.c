/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MK66FN2M0xxx18_Accelerometer.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"

#include "fsl_fxos.h"
#include "fsl_gpio.h"
#include "math.h"
#include "accel.h"

#define SENSOR_ADDRESS 0x1DU
#define DEFAULT_DATA_SCALE 2U
#define BUFFER_SIZE 6

int interruptFlag = 0;

status_t setupOrientationDetection();

/**
 * Configures FXOS8700CQ accelerometer.
 */
status_t initializeAccel() {
    fxos_handle_t fxosHandle = {0};
    fxos_config_t config     = {0};
    status_t result          = kStatus_Fail;

    /* Configure the I2C function */
    config.I2C_SendFunc    = BOARD_Accel_I2C_Send;
    config.I2C_ReceiveFunc = BOARD_Accel_I2C_Receive;
    config.slaveAddress = SENSOR_ADDRESS;

    /* Initialize accelerometer sensor */
    result = startInitialization(&fxosHandle, &config);
    if (result != kStatus_Success)
    {
        PRINTF("\r\nSensor device initialization start failed!\r\n");
        return result;
    }

    result = setupOrientationDetection();
    if (result != kStatus_Success) {
    	PRINTF("\r\nOrientation detection initialization failed!\r\n");
    	return result;
    }

    result = finishInitialization(&fxosHandle, &config);
    if (result != kStatus_Success) {
    	PRINTF("\r\nSensor device initialize finish failed!\r\n");
    	return result;
    }
    return result;
}

status_t setupOrientationDetection() {
	// TODO: setup accelerometer to generate an interrupt when orientation changes
	if (BOARD_Accel_I2C_Send(SENSOR_ADDRESS, 0x11, 1, 0xC0) != kStatus_Success) { // enable portrait/landscape detection
		return kStatus_Fail;
	}
	if (BOARD_Accel_I2C_Send(SENSOR_ADDRESS, 0x2D, 1, 0x10) != kStatus_Success) { // enable interrupt on orientation change
		return kStatus_Fail;
	}
	if (BOARD_Accel_I2C_Send(SENSOR_ADDRESS, 0x2E, 1, 0x10) != kStatus_Success) { // route interrupt to PIN1
			return kStatus_Fail;
	}
    return kStatus_Success;
}

/* PORTC_IRQn interrupt handler */
void GPIOC_IRQHANDLER(void) {
  /* Get pin flags */
  uint32_t pin_flags = GPIO_PortGetInterruptFlags(GPIOC);

  /* Place your interrupt code here */
  interruptFlag++;

  /* Clear pin flags */
  GPIO_PortClearInterruptFlags(GPIOC, pin_flags);

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}



/*
 * @brief   Application entry point.
 */
int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("PV198 - 6. lecture - I2C accelerometer\n");

    if (initializeAccel() != kStatus_Success) {
    	PRINTF("\r\nInitialization failed!\r\n");
    	return -1;
    }

    /*
     * For some reason whenever the orientation changes, the interrupt gets called like 5 times
     * with xyz values being very similar each time. After trying to fix it, but making mikasa09
     * return "init failed" instead, I just left it that way.
     */

    uint8_t data;
    volatile static int i = 0;
    while(1) {
    	BOARD_Accel_I2C_Receive(SENSOR_ADDRESS, 0x10,1,&data,1);
    	if(interruptFlag > 0) {
    		printf("Orientation changed to %x\n", data);
    		interruptFlag = 0;
    	}
    	i++;
    	__asm volatile ("nop");
    }
    return 0;
}
