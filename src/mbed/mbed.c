/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"

/* Counter for milliseconds */
volatile uint32_t msTicks;

/* Handler for SysTick interrupt */
void SysTick_Handler(void) {
	msTicks++;
}

/* Main initialization */
void initSys(uint32_t flags) {
	/* Update system clock register and reset counter. */
	SystemCoreClockUpdate();
	
	/* Initialize global variables. */
	msTicks = 0;
	mbedStatus = 0x0;

	/* Try to initialize the SysTick counter for 1ms interrupt. */
	if (SysTick_Config(SystemCoreClock/1000)) {
		/* Infinite loop on error. */
		while (1) ;
	}

	/* Initialize periphials. */
	if ((mbedStatus ^ MBED_LED_INIT) && (flags & INIT_LED)) {
		initLED();
		ledOn(LED0 | LED1 | LED2 | LED3);
		delay(200);
		ledOff(LED0 | LED1 | LED2 | LED3);
		flags |= MBED_LED_INIT;
	}

	if ((mbedStatus ^ MBED_MUSB_INIT) && (flags & INIT_MUSB)) {
		initMiniUSB(9600);
		flags |= MBED_MUSB_INIT;
	}

	flags |= MBED_SYS_INIT;
}

/* Delay function */
void delay(uint32_t msecs) {
	uint32_t currTickCount = msTicks;

	/* Loop until desired delay is achieved. */
	while ((msTicks - currTickCount) < msecs) ;
}

