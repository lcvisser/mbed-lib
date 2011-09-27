#include "mbed.h"

int main(void) {
	/* Initialize the system. */
	initSys(INIT_LED | INIT_TIMER0);

	/* Alternate LEDs at 2 Hz. */
	while (1) {
		ledOn(LED0 | LED2);
		ledOff(LED1 | LED3);
		delay(MBED_TIMER0, 1000);

		ledOn(LED1 | LED3);
		ledOff(LED0 | LED2);
		delay(MBED_TIMER0, 1000);
	}
	
	return 0;
}

