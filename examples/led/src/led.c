#include "mbed.h"

int main(void) {
	/* Initialize the system. */
	initSys(INIT_LED);

	/* Alternate LEDs at 2 Hz. */
	while (1) {
		turnOnLED(LED0 | LED2);
		turnOffLED(LED1 | LED3);
		wait(250);

		turnOnLED(LED1 | LED3);
		turnOffLED(LED0 | LED2);
		wait(250);
	}
	
	return 0;
}

