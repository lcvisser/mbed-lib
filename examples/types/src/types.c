#include <stdio.h>
#include <string.h>

#include "mbed.h"

#define BUFSIZE	256

/* Forward declarations */
void sizes(void);
void storage(void);

/* Main function */
int main(void) {
	char txbuf[BUFSIZE + 1] = {'\0'};

	/* Initialize the system. */
	initSys(INIT_LED | INIT_MUSB | INIT_TIMER0);
	
	/* Greeting message */
	snprintf(txbuf, BUFSIZE, "\r\nCortex-M3 data type information\r\n");
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));

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

