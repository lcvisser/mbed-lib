/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"

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
	if ( SysTick_Config(SystemCoreClock/1000) ) {
		/* Infinite loop on error. */
		while (1) ;
	}

	/* Initialize periphials. */
	if ( (mbedStatus ^ MBED_MUSB_INIT) && (flags & INIT_MUSB) ) {
		initMiniUSB(_MINI_USB_BAUDRATE);
	}

	if ( (mbedStatus ^ MBED_SERIAL0_INIT) && (flags & INIT_SERIAL0) ) {
		initSerial(MBED_SERIAL0, _SERIAL0_BAUDRATE);
	}

	if ( (mbedStatus ^ MBED_SERIAL1_INIT) && (flags & INIT_SERIAL1) ) {
		initSerial(MBED_SERIAL1, _SERIAL1_BAUDRATE);
	}

	if ( (mbedStatus ^ MBED_SERIAL2_INIT) && (flags & INIT_SERIAL2) ) {
		initSerial(MBED_SERIAL2, _SERIAL2_BAUDRATE);
	}

	if ( (mbedStatus ^ MBED_CAN0_INIT) && (flags & INIT_CAN0) ) {
		initCAN(MBED_CAN0, _CAN0_BAUDRATE);
	}

	if ( (mbedStatus ^ MBED_CAN1_INIT) && (flags & INIT_CAN1) ) {
		initCAN(MBED_CAN1, _CAN1_BAUDRATE);
	}

	if ( (mbedStatus ^ MBED_LED_INIT) && (flags & INIT_LED) ) {
		initLED();
		ledOn(LED0 | LED1 | LED2 | LED3);
		delay(200);
		ledOff(LED0 | LED1 | LED2 | LED3);
	}

	mbedStatus |= MBED_SYS_INIT;
}

/* Delay function */
void delay(uint32_t msecs) {
	uint32_t currTickCount = msTicks;

	/* Loop until desired delay is achieved. */
	while ( (msTicks - currTickCount) < msecs ) ;
}

