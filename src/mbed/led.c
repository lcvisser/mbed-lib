#include "led.h"

/* LED initialization function */
__INLINE static void initLED(void) {
	/* Enable bits 18, 20, 21, 23 as outputs. */
	GPIO_SetDir(1, LEDS, 1);

	/* Turn all LEDs off. */
	GPIO_ClearValue(1, LEDS);
}

/* Turn LED on */
__INLINE static void turnOnLED(uint32_t led) {
	GPIO_SetValue(1, led);
}

/* Turn LED off */
__INLINE static void turnOffLED(uint32_t led) {
	GPIO_ClearValue(1, led);
}


