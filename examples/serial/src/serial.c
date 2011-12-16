#include "mbed.h"

/* Main function */
int main(void) {
	uint8_t c = 0xaa;

	/* Initialize the system. */
	setSerialBaudrate(MBED_SERIAL1, 2400);
	setTimerPrescale(MBED_TIMER0, 1000);
	initSys(INIT_LED | INIT_SERIAL1 | INIT_TIMER0);
	
	while (1) {
		ledOn(MBED_LED0);
		serialSend(MBED_SERIAL1, &c, 1);
		delay(MBED_TIMER0, 500);
		ledOff(MBED_LED0);
		delay(MBED_TIMER0, 500);
	}

	return 0;
}

