/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"

/* Main initialization */
void initSys(uint32_t flags) {
	/* Update system clock register and reset counter. */
	SystemCoreClockUpdate();
	
	/* Initialize global variables. */
	mbedStatus = 0x0;

	/* Intialize timers. */
	if ( (mbedStatus ^ MBED_TIMER0_INIT) && (flags & INIT_TIMER0) ) {
		initTimer(MBED_TIMER0, _TIMER0_PS);
	}

	if ( (mbedStatus ^ MBED_TIMER1_INIT) && (flags & INIT_TIMER1) ) {
		initTimer(MBED_TIMER1, _TIMER1_PS);
	}

	if ( (mbedStatus ^ MBED_TIMER2_INIT) && (flags & INIT_TIMER2) ) {
		initTimer(MBED_TIMER2, _TIMER2_PS);
	}

	if ( (mbedStatus ^ MBED_TIMER3_INIT) && (flags & INIT_TIMER3) ) {
		initTimer(MBED_TIMER3, _TIMER3_PS);
	}

	/* Initialize peripherals. */
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
		if ( mbedStatus & MBED_TIMER0_INIT ) {
			ledOn(LED0 | LED1 | LED2 | LED3);
			delay(MBED_TIMER0, 200);
			ledOff(LED0 | LED1 | LED2 | LED3);
		}
	}

	/* Configure GPIO. */
	if ( (mbedStatus ^ MBED_GPI_INIT) && (flags & INIT_GPI) ) {
		initGPInputs();
	}

	if ( (mbedStatus ^ MBED_GPO_INIT) && (flags & INIT_GPO) ) {
		initGPOutputs();
	}

	mbedStatus |= MBED_SYS_INIT;
}

