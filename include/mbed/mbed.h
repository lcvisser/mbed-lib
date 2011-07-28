/* Copyright (c) 2011 Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#ifndef _MBED_H
#define _MBED_H

#include "LPC17xx.h"
#include "led.h"
#include "mini_usb.h"

/* Initializer flags */
#define INIT_LED	(1 << 1)	/* Initialize the four blue LEDs. */
#define INIT_MUSB	(1 << 2)	/* Initialize the mini USB-B port for serial communication. */

/* Status flags */
#define MBED_SYS_INIT		(1 << 0)
#define MBED_LED_INIT		(1 << 1)
#define MBED_MUSB_INIT		(1 << 2)

uint32_t mbedStatus;

void SysTick_Handler(void);
void initSys(uint32_t);
void wait(uint32_t);

#endif

