/* Copyright (c) 2011 Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "LPC17xx.h"

/* Counter for milliseconds */
volatile uint32_t msTicks;

/* Handler for SysTick interrupt */
void SysTick_Handler(void) {
	msTicks++;
}

/* Main initialization function */
void initSys(void) {
	/* Update system clock register and reset counter. */
	SystemCoreClockUpdate();
	msTicks = 0;

	/* Try to initialize the SysTick counter for 1ms interrupt. */
	if (SysTick_Config(SystemCoreClock/1000)) {
		/* Infinite loop on error. */
		while (1) ;
	}
}

/* Wait function */
void wait(uint32_t msecs) {
	uint32_t currTickCount = msTicks;

	/* Loop until desired delay is achieved. */
	while ((msTicks - currTickCount) < msecs) ;
}

