/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"

/*! \brief System initialization function.
 *
 * This function initializes the LPC1768 clock registers and any other
 * functionality that is required.
 * \param flags		Functionality to be initialized, indicated by setting 
 *			corresponding bits.
 *
 * \sa initflags
 */
void initSys(uint32_t flags) {
	/* Update system clock register and reset counter. */
	SystemCoreClockUpdate();
	
	/* Initialize global variables. */
	mbedStatus = 0x0;

	/* Intialize timers. */
	if ( !(mbedStatus & MBED_TIMER0_INIT) && (flags & INIT_TIMER0) ) {
		initTimer(MBED_TIMER0);
	}

	if ( !(mbedStatus & MBED_TIMER1_INIT) && (flags & INIT_TIMER1) ) {
		initTimer(MBED_TIMER1);
	}

	if ( !(mbedStatus & MBED_TIMER2_INIT) && (flags & INIT_TIMER2) ) {
		initTimer(MBED_TIMER2);
	}

	if ( !(mbedStatus & MBED_TIMER3_INIT) && (flags & INIT_TIMER3) ) {
		initTimer(MBED_TIMER3);
	}

	/* Initialize peripherals. */
	if ( !(mbedStatus & MBED_MUSB_INIT) && (flags & INIT_MUSB) ) {
		initMiniUSB();
	}

	if ( !(mbedStatus & MBED_SERIAL0_INIT) && (flags & INIT_SERIAL0) ) {
		initSerial(MBED_SERIAL0);
	}

	if ( !(mbedStatus & MBED_SERIAL1_INIT) && (flags & INIT_SERIAL1) ) {
		initSerial(MBED_SERIAL1);
	}

	if ( !(mbedStatus & MBED_SERIAL2_INIT) && (flags & INIT_SERIAL2) ) {
		initSerial(MBED_SERIAL2);
	}

	if ( !(mbedStatus & MBED_CAN0_INIT) && (flags & INIT_CAN0) ) {
		initCAN(MBED_CAN0);
	}

	if ( !(mbedStatus & MBED_CAN1_INIT) && (flags & INIT_CAN1) ) {
		initCAN(MBED_CAN1);
	}

	if ( !(mbedStatus & MBED_LED_INIT) && (flags & INIT_LED) ) {
		initLED();
		if (mbedStatus & MBED_TIMER0_INIT) {
			LEDOn(MBED_LED0 | MBED_LED1 | MBED_LED2 | MBED_LED3);
			delay(MBED_TIMER0, 200);
			LEDOff(MBED_LED0 | MBED_LED1 | MBED_LED2 | MBED_LED3);
		}
	}

	/* Configure GPIO. */
	if ( !(mbedStatus & MBED_GPI_INIT) && (flags & INIT_GPI) ) {
		initGPInputs();
	}

	if ( !(mbedStatus & MBED_GPO_INIT) && (flags & INIT_GPO) ) {
		initGPOutputs();
	}

	/* Update status flags. */
	mbedStatus |= MBED_SYS_INIT;
}

