/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "LPC17xx.h"
#include "can.h"
#include "led.h"
#include "mini_usb.h"
#include "serial.h"

/* Initializer flags */
#define INIT_LED	(1 << 1)	/* Initialize the four blue LEDs. */
#define INIT_MUSB	(1 << 2)	/* Serial on mini USB-B port (UART0). */
#define INIT_SERIAL0	(1 << 3)	/* Serial on DIP 13/14 (UART1). */
#define INIT_SERIAL1	(1 << 3)	/* Serial on DIP 27/28 (UART2). */
#define INIT_SERIAL2	(1 << 4)	/* Serial on DIP 9/10 (UART3). */
#define INIT_CAN0	(1 << 5)	/* CAN on DIP 9/10 (CAN1). */
#define INIT_CAN1	(1 << 6)	/* CAN on DIP 29/30 (CAN2). */

/* Status flags */
#define MBED_SYS_INIT		(1 << 0)
#define MBED_LED_INIT		(1 << 1)
#define MBED_MUSB_INIT		(1 << 2)
#define MBED_SERIAL0_INIT	(1 << 3)
#define MBED_SERIAL1_INIT	(1 << 4)
#define MBED_SERIAL2_INIT	(1 << 5)
#define MBED_CAN0_INIT		(1 << 6)
#define MBED_CAN1_INIT		(1 << 7)

/* Available ports */
#define MBED_SERIAL0	0	/* On DIP 13/14 */
#define MBED_SERIAL1	1	/* On DIP 27/28 */
#define MBED_SERIAL2	2	/* On DIP 9/10 */
#define MBED_CAN0	0	/* On DIP 9/10 */
#define MBED_CAN1	1	/* On DIP 29/30 */

#ifndef _MBED_H
#define _MBED_H

/* Counter for milliseconds */
volatile uint32_t msTicks;

/* Global status flags */
volatile uint32_t mbedStatus;

/* Utility functions */
void SysTick_Handler(void);
void initSys(uint32_t);
void delay(uint32_t);

#endif

