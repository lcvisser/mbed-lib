/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

/*!
 * \file
 *
 * In this file are all necessary defines for the mbed platform. Also, all
 * all header files are included here for convience, so that including this
 * header file is sufficient.
 */

#include "LPC17xx.h"
#include "mbed_can.h"
#include "mbed_gpio.h"
#include "mbed_led.h"
#include "mbed_musb.h"
#include "mbed_serial.h"
#include "mbed_timer.h"

#ifndef MBED_H
#define MBED_H

/* Initialization flags */
#define INIT_LED	(1 << 1)	/*!< Initialize the four blue LEDs. */
#define INIT_MUSB	(1 << 2)	/*!< Serial on mini USB-B port (UART0). */
#define INIT_SERIAL0	(1 << 3)	/*!< Serial on DIP 13/14 (UART1). */
#define INIT_SERIAL1	(1 << 4)	/*!< Serial on DIP 27/28 (UART2). */
#define INIT_SERIAL2	(1 << 5)	/*!< Serial on DIP 9/10 (UART3). */
#define INIT_CAN0	(1 << 6)	/*!< CAN on DIP 9/10 (CAN1). */
#define INIT_CAN1	(1 << 7)	/*!< CAN on DIP 29/30 (CAN2). */
#define INIT_TIMER0	(1 << 8)	/*!< Initialize TIMER0. */
#define INIT_TIMER1	(1 << 9)	/*!< Initialize TIMER1. */
#define INIT_TIMER2	(1 << 10)	/*!< Initialize TIMER2. */
#define INIT_TIMER3	(1 << 11)	/*!< Initialize TIMER3. */
#define INIT_GPI	(1 << 12)	/*!< Initialize general purpose input ports. */
#define INIT_GPO	(1 << 13)	/*!< Initialize general purpose output ports. */

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
#define MBED_GPI_INIT		(1 << 12)
#define MBED_GPO_INIT		(1 << 13)

/* General purpose I/O */
#define MBED_GPIOX	(1 << 0)	/* Not configured */
#define MBED_GPIO5	(1 << 1)	/* On DIP 5 */
#define MBED_GPIO6	(1 << 2)	/* On DIP 6 */
#define MBED_GPIO7	(1 << 3)	/* On DIP 7 */
#define MBED_GPIO8	(1 << 4)	/* On DIP 8 */
#define MBED_GPIO9	(1 << 5)	/* On DIP 9 */
#define MBED_GPIO10	(1 << 6)	/* On DIP 10 */
#define MBED_GPIO11	(1 << 7)	/* On DIP 11 */
#define MBED_GPIO12	(1 << 8)	/* On DIP 12 */
#define MBED_GPIO13	(1 << 9)	/* On DIP 13 */
#define MBED_GPIO14	(1 << 10)	/* On DIP 14 */
#define MBED_GPIO15	(1 << 11)	/* On DIP 15 */
#define MBED_GPIO16	(1 << 12)	/* On DIP 16 */
#define MBED_GPIO17	(1 << 13)	/* On DIP 17 */
#define MBED_GPIO18	(1 << 14)	/* On DIP 18 */
#define MBED_GPIO19	(1 << 15)	/* On DIP 19 */
#define MBED_GPIO20	(1 << 16)	/* On DIP 20 */
#define MBED_GPIO21	(1 << 17)	/* On DIP 21 */
#define MBED_GPIO22	(1 << 18)	/* On DIP 22 */
#define MBED_GPIO23	(1 << 19)	/* On DIP 23 */
#define MBED_GPIO24	(1 << 20)	/* On DIP 24 */
#define MBED_GPIO25	(1 << 21)	/* On DIP 25 */
#define MBED_GPIO26	(1 << 22)	/* On DIP 26 */
#define MBED_GPIO27	(1 << 23)	/* On DIP 27 */
#define MBED_GPIO28	(1 << 24)	/* On DIP 28 */
#define MBED_GPIO29	(1 << 25)	/* On DIP 29 */
#define MBED_GPIO30	(1 << 26)	/* On DIP 30 */

/* Available ports */
#define MBED_GPIO_P0	(MBED_GPIO5 | MBED_GPIO6 | MBED_GPIO7 | MBED_GPIO8 | MBED_GPIO9 | MBED_GPIO10 | MBED_GPIO11 | MBED_GPIO12 | MBED_GPIO13 | MBED_GPIO14 | MBED_GPIO15 | MBED_GPIO16 | MBED_GPIO17 | MBED_GPIO18 | MBED_GPIO27 | MBED_GPIO28 | MBED_GPIO29 | MBED_GPIO30)
#define MBED_GPIO_P1	(MBED_GPIO19 | MBED_GPIO20)
#define MBED_GPIO_P2	(MBED_GPIO21 | MBED_GPIO22 | MBED_GPIO23 | MBED_GPIO24 | MBED_GPIO25 | MBED_GPIO26)

#define MBED_SERIAL0	0		/* On DIP 13/14 */
#define MBED_SERIAL1	1		/* On DIP 27/28 */
#define MBED_SERIAL2	2		/* On DIP 9/10 */
#define MBED_CAN0	0		/* On DIP 9/10 */
#define MBED_CAN1	1		/* On DIP 29/30 */

/* Devices */
#define MBED_TIMER0	0		/* Timer 0 */
#define MBED_TIMER1	1		/* Timer 1 */
#define MBED_TIMER2	2		/* Timer 2 */
#define MBED_TIMER3	3		/* Timer 3 */

/* Global status flags */
volatile uint32_t mbedStatus;

/* Utility functions */
void initSys(uint32_t);

#endif

