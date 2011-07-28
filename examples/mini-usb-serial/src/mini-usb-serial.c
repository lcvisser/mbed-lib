#include <string.h>

#include "mbed.h"

extern uint32_t msTicks;

/* Main function */
int main(void) {
	char greeting[] = "Hello World!\r\n";

	/* Initialize the system. */
	initSys(INIT_LED | INIT_MUSB);
	
	while (1) {
		turnOnLED(LED3);
		UART_Send(LPC_UART0, (uint8_t *)greeting, strlen(greeting), BLOCKING);
		wait(200);
		turnOffLED(LED3);
		wait(800);
	}

	return 0;
}

