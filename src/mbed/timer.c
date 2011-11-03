/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"

/* Prescaling values in microseconds */
volatile static uint32_t _timerPS0;
volatile static uint32_t _timerPS1;
volatile static uint32_t _timerPS2;
volatile static uint32_t _timerPS3;

void setTimerPrescale(uint8_t timerID, uint32_t usScaling) {
	switch (timerID) {
		case MBED_TIMER0:
			_timerPS0 = usScaling;
			break;
		case MBED_TIMER1:
			_timerPS1 = usScaling;
			break;
		case MBED_TIMER2:
			_timerPS2 = usScaling;
			break;
		case MBED_TIMER3:
			_timerPS3 = usScaling;
			break;
		default:
			break;
	}
}

void initTimer(uint8_t timerID) {
	TIM_TIMERCFG_Type timerConfig;

	/* Set timer configuration options. */
	timerConfig.PrescaleOption = TIM_PRESCALE_USVAL;

	/* Initialize timer. */
	switch (timerID) {
		case MBED_TIMER0:
			/* Check for initialization. */
			if ( mbedStatus & MBED_TIMER0_INIT ) {
				return;
			}

			timerConfig.PrescaleValue = _timerPS0;
			TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timerConfig);
			startTimer(MBED_TIMER0);
			
			mbedStatus |= MBED_TIMER0_INIT;
			
			break;
		case MBED_TIMER1:
			/* Check for initialization. */
			if ( mbedStatus & MBED_TIMER1_INIT ) {
				return;
			}

			timerConfig.PrescaleValue = _timerPS1;
			TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &timerConfig);
			startTimer(MBED_TIMER1);
			
			mbedStatus |= MBED_TIMER1_INIT;
			
			break;
		case MBED_TIMER2:
			/* Check for initialization. */
			if ( mbedStatus & MBED_TIMER2_INIT ) {
				return;
			}

			timerConfig.PrescaleValue = _timerPS2;
			TIM_Init(LPC_TIM2, TIM_TIMER_MODE, &timerConfig);
			startTimer(MBED_TIMER2);
			
			mbedStatus |= MBED_TIMER2_INIT;
			
			break;
		case MBED_TIMER3:
			/* Check for initialization. */
			if ( mbedStatus & MBED_TIMER3_INIT ) {
				return;
			}

			timerConfig.PrescaleValue = _timerPS3;
			TIM_Init(LPC_TIM3, TIM_TIMER_MODE, &timerConfig);
			startTimer(MBED_TIMER3);

			mbedStatus |= MBED_TIMER3_INIT;
			
			break;
		default:
			break;
	}
}

void startTimer(uint8_t timerID) {
	switch (timerID) {
		case MBED_TIMER0:
			TIM_Cmd(LPC_TIM0, ENABLE);
			break;
		case MBED_TIMER1:
			TIM_Cmd(LPC_TIM1, ENABLE);
			break;
		case MBED_TIMER2:
			TIM_Cmd(LPC_TIM2, ENABLE);
			break;
		case MBED_TIMER3:
			TIM_Cmd(LPC_TIM3, ENABLE);
			break;
		default:
			break;
	}
}

void stopTimer(uint8_t timerID) {
	switch (timerID) {
		case MBED_TIMER0:
			TIM_Cmd(LPC_TIM0, DISABLE);
			break;
		case MBED_TIMER1:
			TIM_Cmd(LPC_TIM1, DISABLE);
			break;
		case MBED_TIMER2:
			TIM_Cmd(LPC_TIM2, DISABLE);
			break;
		case MBED_TIMER3:
			TIM_Cmd(LPC_TIM3, DISABLE);
			break;
		default:
			break;
	}
}

void resetTimer(uint8_t timerID) {
	switch (timerID) {
		case MBED_TIMER0:
			TIM_ResetCounter(LPC_TIM0);
			break;
		case MBED_TIMER1:
			TIM_ResetCounter(LPC_TIM1);
			break;
		case MBED_TIMER2:
			TIM_ResetCounter(LPC_TIM2);
			break;
		case MBED_TIMER3:
			TIM_ResetCounter(LPC_TIM3);
			break;
		default:
			break;
	}
}

uint32_t getTimerVal(uint8_t timerID) {
	uint32_t r = 0;

	switch (timerID) {
		case MBED_TIMER0:
			r = LPC_TIM0->TC;
			break;
		case MBED_TIMER1:
			r = LPC_TIM1->TC;
			break;
		case MBED_TIMER2:
			r = LPC_TIM2->TC;
			break;
		case MBED_TIMER3:
			r = LPC_TIM3->TC;
			break;
		default:
			break;
	}

	return r;
}

void delay(uint8_t timerID, uint32_t val) {
	uint32_t start = getTimerVal(timerID);

	/* Loop until delay is achieved. */
	while ( (getTimerVal(timerID) - start) < val) ;
}

