/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"
#include "led.h"

/* LED initialization function */
void initLED(void) {
	/* Check for initialization. */
	if (mbedStatus & MBED_LED_INIT) {
		return;
	}

	/* Enable bits corresponding to LEDs as outputs. */
	GPIO_SetDir(1, LED0 | LED1 | LED2 | LED3, 1);

	/* Turn off all LEDs. */
	GPIO_ClearValue(1, LED0 | LED1 | LED2 | LED3);

	/* Update status flags. */
	mbedStatus |= MBED_LED_INIT;
}

/* Turn LED on */
void ledOn(uint32_t led) {
	GPIO_SetValue(1, led);
}

/* Turn LED off */
void ledOff(uint32_t led) {
	GPIO_ClearValue(1, led);
}

/* Toggle LED */
void ledToggle(uint32_t led) {
	/* TODO */
}

