/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "LPC17xx.h"
#include "lpc17xx_gpio.h"

#ifndef MBED_LED_H
#define MBED_LED_H

#define MBED_LED0	(1 << 18)
#define MBED_LED1	(1 << 20)
#define MBED_LED2	(1 << 21)
#define MBED_LED3	(1 << 23)

void initLED(void);
void LEDOn(uint32_t);
void LEDOff(uint32_t);
void LEDToggle(uint32_t);

#endif

