/* Copyright (c) 2011 Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#ifndef _LED_H
#define _LED_H

#include "LPC17xx.h"
#include "lpc17xx_gpio.h"

#define LED0	(1 << 18)
#define LED1	(1 << 20)
#define LED2	(1 << 21)
#define LED3	(1 << 23)

void initLED(void);
void turnOnLED(uint32_t);
void turnOffLED(uint32_t);

#endif

