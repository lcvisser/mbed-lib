/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"

/* LED initialization function */
void initLED(void) {
	PINSEL_CFG_Type pinConfig;

	/* Check for initialization. */
	if (mbedStatus & MBED_LED_INIT) {
		return;
	}

	/* Configure pins */
	pinConfig.OpenDrain = PINSEL_PINMODE_NORMAL;
	pinConfig.Pinmode = PINSEL_PINMODE_PULLUP;
	pinConfig.Funcnum = PINSEL_FUNC_0;
	pinConfig.Portnum = PINSEL_PORT_1;
	pinConfig.Pinnum = 18;		// LED 0
	PINSEL_ConfigPin(&pinConfig);
	pinConfig.Pinnum = 20;		// LED 1
	PINSEL_ConfigPin(&pinConfig);
	pinConfig.Pinnum = 21;		// LED 2
	PINSEL_ConfigPin(&pinConfig);
	pinConfig.Pinnum = 23;		// LED 3
	PINSEL_ConfigPin(&pinConfig);

	/* Enable bits corresponding to LEDs as outputs. */
	GPIO_SetDir(1, MBED_LED0 | MBED_LED1 | MBED_LED2 | MBED_LED3, 1);

	/* Turn off all MBED_MBED_LEDs. */
	GPIO_ClearValue(1, MBED_LED0 | MBED_LED1 | MBED_LED2 | MBED_LED3);

	/* Update status flags. */
	mbedStatus |= MBED_LED_INIT;
}

/* Turn LED on */
void LEDOn(uint32_t led) {
	GPIO_SetValue(1, led);
}

/* Turn LED off */
void LEDOff(uint32_t led) {
	GPIO_ClearValue(1, led);
}

/* Toggle LED */
void LEDToggle(uint32_t led) {
	uint32_t ledStatus;

	ledStatus = GPIO_ReadValue(1);
	if (ledStatus & led) {
		GPIO_ClearValue(1, led);
	} else {
		GPIO_SetValue(1, led);
	}
}

