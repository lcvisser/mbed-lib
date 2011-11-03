#include <stdio.h>
#include <string.h>

#include "mbed.h"

/* Forward declarations */
void sizes(void);
void storage(void);

/* Main function */
int main(void) {
	/* Initialize the system. */
	setMiniUSBBaudrate(9600);
	setTimerPrescale(MBED_TIMER0, 1000);
	initSys(INIT_LED | INIT_MUSB | INIT_TIMER0);
	
	/* Greeting message */
	miniUSBPrint("\r\nCortex-M3 data type information\r\n");

	/* Run tests */
	sizes();
	storage();
	
	/* Loop forever */
	while (1) {
		ledOn(LED0);
		delay(MBED_TIMER0, 100);
		ledOff(LED0);
		delay(MBED_TIMER0, 100);
	}

	return 0;
}

