#include "mbed.h"

int main(void) {
	/* Initialize the system. */
	setTimerPrescale(MBED_TIMER0, 1000);	/* 1ms interval */
	initSys(INIT_LED | INIT_TIMER0);

	/* Alternate LEDs at 2 Hz. */
	while (1) {
		ledOn(MBED_LED0 | MBED_LED2);
		ledOff(MBED_LED1 | MBED_LED3);
		delay(MBED_TIMER0, 500);

		ledOn(MBED_LED1 | MBED_LED3);
		ledOff(MBED_LED0 | MBED_LED2);
		delay(MBED_TIMER0, 500);
	}
	
	return 0;
}

