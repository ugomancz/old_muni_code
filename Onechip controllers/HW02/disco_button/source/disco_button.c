/*
 * Copyright 2016-2020 NXP
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
 * @file    MK66FN2M0xxx18_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

void toggleRGB(int color, int onOff);

int main(void)
{

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    short LEDFlag = 0; // signal whether LED should be on or off
    short waitFlag = 0; // ignore presses of the button when it's already pressed
    short RGBCounter = 0; // serves to cycle the RGB
    while(1) {
        if (LEDFlag) {
        	toggleRGB(RGBCounter % 3, 1);
        } else {
        	toggleRGB(RGBCounter % 3, 0);
        }
        uint32_t input = GPIO_PinRead(BOARD_BTN_RIGHT_GPIO, BOARD_BTN_RIGHT_PIN);
        if (input && waitFlag) waitFlag = 0; // button not pressed anymore
        if (!input && !LEDFlag && !waitFlag) {
        	LEDFlag++;
        	waitFlag++;
        	RGBCounter++; // move on to the next color
        } else if (!input && LEDFlag && !waitFlag) {
        	LEDFlag = 0;
        	waitFlag++;
        }
    }
    return 0;
}
/*
 * Switches given color LED on or off
 */
void toggleRGB(int color, int onOff)
{
	switch (color) {
	case 0: // red
		if (onOff) {
			LED_RED_ON();
        } else {
			LED_RED_OFF();
        }
		break;
	case 1: // green
		if (onOff) {
			LED_GREEN_ON();
		} else {
			LED_GREEN_OFF();
		}
		break;
	case 2: // blue
		if (onOff) {
			LED_BLUE_ON();
		} else {
			LED_BLUE_OFF();
		}
		break;
	}
}
