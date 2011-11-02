#include <stdio.h>
#include <string.h>

#include "mbed.h"

#define RBSIZE		100

volatile int buffer[RBSIZE];
volatile int* readPtr;
volatile int* writePtr;

int readValue() {
	int value;

	if ( readPtr == writePtr ) {
		// Buffer is empty
		return -1;
	} else {
		value = *readPtr;
		if ( readPtr == &buffer[RBSIZE - 1] ) {
			readPtr = &buffer[0];
		} else {
			readPtr++;
		}

		return value;
	}
}

void writeValue(void) {
	*writePtr *= 2;;

	if ( writePtr == &buffer[RBSIZE - 1] ) {
		writePtr = &buffer[0];
	} else {
		writePtr++;
	}
}

/* SysTick interrupt handler */
void SysTick_Handler(void) {
	/* Disable interrupt */
	__disable_irq();

	writeValue();

	/* Enable interrupt */
	__enable_irq();
}

/* Main function */
int main(void) {
	int i = 0;

	/* Initialize the system */
	initSys(INIT_LED | INIT_MUSB | INIT_TIMER0);

	readPtr = &buffer[0];
	writePtr = &buffer[4];

	/* Initialize the SysTick counter to 0.1 sec intervals */
	if ( SysTick_Config(SystemCoreClock/10) ) {
		/* Error, loop forever */
		while (1) {
			ledOn(LED0 | LED1 | LED2 | LED3);
			delay(MBED_TIMER0, 100);
			ledOff(LED0 | LED1 | LED2 | LED3);
			delay(MBED_TIMER0, 100);
		}
	}

	/* Fill buffer */
	for ( i = 0; i < RBSIZE; i++) {
		buffer[i] = i;
	}

	/* Greeting message */
	miniUSBPrint("\r\nRing buffer example\r\n");

	/* Loop forever */
	while (1) {
		ledOn(LED0);
		delay(MBED_TIMER0, 250);

		i = readValue();
		if (i >= 0) {
			miniUSBPrint("Reading buffer:\r\n");
		}

		while (i >= 0) {
			miniUSBPrint("Value: %i\r\n", i);
			i = readValue();
		}

		ledOff(LED0);
		delay(MBED_TIMER0, 250);
	}

	return 0;
}

