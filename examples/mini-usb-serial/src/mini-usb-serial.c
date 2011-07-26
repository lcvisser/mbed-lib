#include <string.h>

#include "led.h"
#include "mini_usb.h"
#include "util.h"

/* Main function */
int main(void) {
	char greeting[] = "Hello World!\n";

	/* Initialize the system. */
	initSys();
	initLED();
	initMiniUSB();

	while (1) {
		turnOnLED(LED0);
		UART_Send(LPC_UART0, (uint8_t *)greeting, strlen(greeting), BLOCKING);
		wait(200);
		turnOffLED(LED0);
		wait(1000);
	}

	return 0;
}

