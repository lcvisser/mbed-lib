/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "LPC17xx.h"
#include "mbed_can.h"
#include "mbed_led.h"
#include "mbed_mini_usb.h"
#include "mbed_serial.h"
#include "mbed_timer.h"

/* Initializer flags */
#define INIT_LED	(1 << 1)	/* Initialize the four blue LEDs. */
#define INIT_MUSB	(1 << 2)	/* Serial on mini USB-B port (UART0). */
#define INIT_SERIAL0	(1 << 3)	/* Serial on DIP 13/14 (UART1). */
#define INIT_SERIAL1	(1 << 4)	/* Serial on DIP 27/28 (UART2). */
#define INIT_SERIAL2	(1 << 5)	/* Serial on DIP 9/10 (UART3). */
#define INIT_CAN0	(1 << 6)	/* CAN on DIP 9/10 (CAN1). */
#define INIT_CAN1	(1 << 7)	/* CAN on DIP 29/30 (CAN2). */
#define INIT_TIMER0	(1 << 8)	/* Initialize TIMER0. */
#define INIT_TIMER1	(1 << 9)	/* Initialize TIMER1. */
#define INIT_TIMER2	(1 << 10)	/* Initialize TIMER2. */
#define INIT_TIMER3	(1 << 11)	/* Initialize TIMER3. */

/* Status flags */
#define MBED_SYS_INIT		(1 << 0)
#define MBED_LED_INIT		(1 << 1)
#define MBED_MUSB_INIT		(1 << 2)
#define MBED_SERIAL0_INIT	(1 << 3)
#define MBED_SERIAL1_INIT	(1 << 4)
#define MBED_SERIAL2_INIT	(1 << 5)
#define MBED_CAN0_INIT		(1 << 6)
#define MBED_CAN1_INIT		(1 << 7)
#define MBED_TIMER0_INIT	(1 << 8)
#define MBED_TIMER1_INIT	(1 << 9)
#define MBED_TIMER2_INIT	(1 << 10)
#define MBED_TIMER3_INIT	(1 << 11)

/* Available ports */
#define MBED_SERIAL0	0	/* On DIP 13/14 */
#define MBED_SERIAL1	1	/* On DIP 27/28 */
#define MBED_SERIAL2	2	/* On DIP 9/10 */
#define MBED_CAN0	0	/* On DIP 9/10 */
#define MBED_CAN1	1	/* On DIP 29/30 */

/* Devices */
#define MBED_TIMER0	0	/* Timer 0 */
#define MBED_TIMER1	1	/* Timer 1 */
#define MBED_TIMER2	2	/* Timer 2 */
#define MBED_TIMER3	3	/* Timer 3 */

#ifndef _MBED_H
#define _MBED_H

/* Global status flags */
volatile uint32_t mbedStatus;

/* Utility functions */
void initSys(uint32_t);

#endif

