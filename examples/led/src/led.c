#include "mbed.h"

int main(void) {
	/* Initialize the system. */
	initSys(INIT_LED);

	/* Alternate LEDs at 2 Hz. */
	while (1) {
		ledOn(LED0 | LED2);
		ledOff(LED1 | LED3);
		delay(250);

		ledOn(LED1 | LED3);
		ledOff(LED0 | LED2);
		delay(250);
	}
	
	return 0;
}

