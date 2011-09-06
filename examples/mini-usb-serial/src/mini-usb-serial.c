#include <string.h>

#include "mbed.h"

/* Main function */
int main(void) {
	char greeting[] = "Hello World!\r\n";

	/* Initialize the system. */
	initSys(INIT_LED | INIT_MUSB);
	
	while (1) {
		ledOn(LED0);
		miniUSBSend((uint8_t *)greeting, strlen(greeting));
		wait(200);
		ledOff(LED0);
		wait(800);
	}

	return 0;
}

