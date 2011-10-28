#include <string.h>

#include "mbed.h"

/* Main function */
int main(void) {
	char greeting[] = "Hello World!\r\n";

	/* Initialize the system. */
	initSys(INIT_LED | INIT_MUSB | INIT_TIMER0);
	
	while (1) {
		ledOn(LED0);
		miniUSBSend((uint8_t*)greeting, strlen(greeting));
		delay(MBED_TIMER0, 500);
		ledOff(LED0);
		delay(MBED_TIMER0, 500);
	}

	return 0;
}

