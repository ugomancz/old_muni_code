/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_pit.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* BOARD_InitPeripherals defines for PIT */
/* Definition of peripheral ID. */
#define PIT_PERIPHERAL PIT
/* Definition of clock source. */
#define PIT_CLOCK_SOURCE kCLOCK_BusClk
/* Definition of clock source frequency. */
#define PIT_CLK_FREQ 60000000UL
/* Definition of ticks count for channel 0 - deprecated. */
#define PIT_0_TICKS 599999999U
/* Definition of ticks count for channel 1 - deprecated. */
#define PIT_1_TICKS 8U
/* PIT interrupt vector ID (number) - deprecated. */
#define PIT_1_IRQN PIT1_IRQn
/* Definition of channel number for channel 0. */
#define PIT_CHANNEL_0 kPIT_Chnl_0
/* Definition of channel number for channel 1. */
#define PIT_CHANNEL_1 kPIT_Chnl_1
/* Definition of ticks count for channel 0. */
#define PIT_CHANNEL_0_TICKS 599999999U
/* Definition of ticks count for channel 1. */
#define PIT_CHANNEL_1_TICKS 8U
/* PIT interrupt vector ID (number). */
#define PIT_CHANNEL_1_IRQN PIT1_IRQn
/* PIT interrupt handler identifier. */
#define TIMER_INTERRUPT PIT1_IRQHandler

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const pit_config_t PIT_config;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
