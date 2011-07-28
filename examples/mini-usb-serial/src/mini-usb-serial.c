#include <string.h>

#include "mbed.h"
#include "led.h"
#include "mini_usb.h"

extern uint32_t msTicks;

/* Main function */
int main(void) {
	char greeting[] = "Hello World!\r\n";

	/* Initialize the system. */
	initSys();
	initLED();
	initMiniUSB(9600);
	
	while (1) {
		turnOnLED(LED0);
		UART_Send(LPC_UART0, (uint8_t *)greeting, strlen(greeting), BLOCKING);
		wait(200);
		turnOffLED(LED0);
		wait(800);
	}

	return 0;
}

