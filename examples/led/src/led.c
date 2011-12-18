#include "mbed.h"

int main(void) {
	/* Initialize the system. */
	setTimerPrescale(MBED_TIMER0, 1000);	/* 1ms interval */
	initSys(INIT_LED | INIT_TIMER0);
	LEDOn(MBED_LED0 | MBED_LED2);
	LEDOff(MBED_LED1 | MBED_LED3);

	/* Alternate LEDs at 2 Hz. */
	while (1) {
		LEDToggle(MBED_LED0 | MBED_LED2);
		LEDToggle(MBED_LED1 | MBED_LED3);
		delay(MBED_TIMER0, 500);
	}
	
	return 0;
}

