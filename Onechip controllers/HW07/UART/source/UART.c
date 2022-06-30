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
 * @file    UART.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"
#include "cir_buffer.h"

#define BUFFER_SIZE 250

bool transmiting = false;
cir_buffer_handle buffer;
uint8_t *data;

/* Puts a string into the circular buffer */
void put_string_buff(cir_buffer_handle buffer_handle, const char *string) {
    for (int i = 0; i < strlen(string); i++) {
        cir_buffer_put(buffer_handle, string[i]);
    }
    cir_buffer_put(buffer_handle, 0);
}

void nonblocking_puts(const char *string){
	//Fill buffer here, note : C strings are ending with '\0'
	put_string_buff(buffer, string);

	//Keep this here, it enables the transmission only when there are data to send
	if(!transmiting){
		transmiting = true;
		UART_EnableInterrupts(UART_PERIPHERAL, kUART_TxDataRegEmptyInterruptEnable);
	}
}

void UART_SERIAL_RX_TX_IRQHANDLER(void){
	uint32_t mask = UART_GetStatusFlags(UART_PERIPHERAL);

	if(kUART_RxDataRegFullFlag & mask){
		UART_WriteByte(UART_PERIPHERAL, UART_ReadByte(UART_PERIPHERAL));
	}
	if(kUART_TransmissionCompleteFlag & mask){
		if (!cir_buf_empty(buffer)) {
			uint8_t letter;
			cir_buf_get(buffer, &letter);
			if (letter != 0) {
				UART_WriteByte(UART_PERIPHERAL, letter);
			}
		} else {
			transmiting = false;
			UART_DisableInterrupts(UART_PERIPHERAL, kUART_TxDataRegEmptyInterruptEnable);
		}
	}
	// We do not clear mask here, HW is doing it for us in case there is reason to clear
}

void PIT_1_1_IRQHANDLER(void){
	PIT_ClearStatusFlags(PIT,kPIT_Chnl_1,kPIT_TimerFlag);
	nonblocking_puts("You are awesome \r\n");
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

	PRINTF("Hello World\n");
	data = malloc(BUFFER_SIZE);
	buffer = cir_buffer_init(data, BUFFER_SIZE);
	while (1) {
		/*UART_ReadBlocking(UART_PERIPHERAL, &data, sizeof(data));
		UART_WriteBlocking(UART_PERIPHERAL, &data, sizeof(data));*/
		// TODO: Create echo using UART_ReadBlocking / UART_WriteBlocking
	}
	return 0;
}
