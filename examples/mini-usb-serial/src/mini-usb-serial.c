#include "mbed.h"

/* Main function */
int main(void) {
	/* Initialize the system. */
	setMiniUSBBaudrate(9600);
	setTimerPrescale(MBED_TIMER0, 1000);
	initSys(INIT_LED | INIT_MUSB | INIT_TIMER0);
	
	while (1) {
		LEDOn(MBED_LED0);
		miniUSBPrint("Hello World! This mbed has been running for %0.3f seconds...\r\n", getTimerVal(MBED_TIMER0)/1000.0);
		delay(MBED_TIMER0, 500);
		LEDOff(MBED_LED0);
		delay(MBED_TIMER0, 500);
	}

	return 0;
}

