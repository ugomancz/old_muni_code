/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"
#include "lcd.h"
#include "fsl_rtc.h"

// definition of positions on the screen
#define NUM_POS 3
#define ZERO_CHAR_VAL 48

/* RTC second interrupt handler */
bool update_rdt = true;

void RTC_1_SECONDS_IRQHANDLER(void) {
	update_rdt = true;
}

/* Recalculates ADC input to percentage*/
int to_percent(int number)
{
	float temp = (float) number / (float) 4096;
    return (temp * 100) + 0.5;
}

// 0.56 V
int main(void)
{
    char x_str[] = "X: 000%";
    char y_str[] = "Y: 000%";

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

    // Initialize the LCD
    LCD_4BitsInit(BOARD_BOOTCLOCKRUN_CORE_CLOCK, false, false);

    // main loop of the demo application
    while (1)
    {
    	// read values from ADC
    	int x = to_percent(ADC16_GetChannelConversionValue(ADC0_PERIPHERAL, 0));
    	int y = to_percent(ADC16_GetChannelConversionValue(ADC1_PERIPHERAL, 0));

    	// parse read values to strings
    	x_str[NUM_POS] = (x / 100) + ZERO_CHAR_VAL;
    	x_str[NUM_POS + 1] = ((x / 10) % 10) + ZERO_CHAR_VAL;
    	x_str[NUM_POS + 2] = (x % 10) + ZERO_CHAR_VAL;

    	y_str[NUM_POS] = (y / 100) + ZERO_CHAR_VAL;
    	y_str[NUM_POS + 1] = ((y / 10) % 10) + ZERO_CHAR_VAL;
    	y_str[NUM_POS + 2] = (y % 10) + ZERO_CHAR_VAL;

		// display the reading
		LCD_SetPosition(0, 0);
		LCD_Print(x_str);
		LCD_SetPosition(0, 1);
		LCD_Print(y_str);

		// wait for next second
		__WFI();

    }
}
