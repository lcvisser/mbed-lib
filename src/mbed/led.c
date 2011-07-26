#include "led.h"

/* LED initialization function */
void initLED(void) {
	/* Enable bits corresponding to LEDs as outputs. */
	GPIO_SetDir(1, LED0 | LED1 | LED2 | LED3, 1);

	/* Turn off all LEDs off. */
	GPIO_ClearValue(1, LED0 | LED1 | LED2 | LED3);
}

/* Turn LED on */
void turnOnLED(uint32_t led) {
	GPIO_SetValue(1, led);
}

/* Turn LED off */
void turnOffLED(uint32_t led) {
	GPIO_ClearValue(1, led);
}


