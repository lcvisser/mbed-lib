#include <stdio.h>
#include <string.h>

#include "mbed.h"

#define RBSIZE		10

unsigned char buffer[RBSIZE];
unsigned char* readPtr;
unsigned char* writePtr;

/* Pointer increment function */
unsigned char* increment(unsigned char* const ptr) {
	unsigned char* inc = NULL;

	/* Check if we are at the end of the buffer */
	if ( ptr == &buffer[RBSIZE - 1] ) {
		inc = &buffer[0];
	} else {
		inc = ptr + sizeof(unsigned char);
	}
	return inc;
}

/* Read function */
unsigned char readValue() {
	unsigned char value;

	if ( readPtr == writePtr ) {
		// Buffer is empty
		return '0';
	} else {
		value = *readPtr;
		readPtr = increment(readPtr);

		return value;
	}
}

/* Write function */
void writeValue(unsigned char c) {
	if ( increment(writePtr) == readPtr) {
		// Buffer is full
	} else {
		*writePtr = c;
		writePtr = increment(writePtr);
	}
}

/* UART0 interrupt handler */
void UART0_IRQHandler(void) {
	/* Disable interrupt */
	NVIC_DisableIRQ(UART0_IRQn);

	ledOn(LED1);
	while (UART_GetLineStatus(LPC_UART0) & UART_LINESTAT_RDR) {
		writeValue((unsigned char)UART_ReceiveByte(LPC_UART0));
	}
	delay(MBED_TIMER0, 50);
	ledOff(LED1);

	/* Enable interrupt */
	NVIC_EnableIRQ(UART0_IRQn);
}

/* Main function */
int main(void) {
	unsigned char c = '0';

	/* Initialize the system */
	setMiniUSBBaudrate(9600);
	setTimerPrescale(MBED_TIMER0, 1000);
	initSys(INIT_LED | INIT_MUSB | INIT_TIMER0);

	memset((void*)buffer, '0', RBSIZE);
	readPtr = &buffer[0];
	writePtr = &buffer[0];

	/* Enable interrupt */
	UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);
	UART_IntConfig(LPC_UART0, UART_INTCFG_RLS, ENABLE);
	NVIC_EnableIRQ(UART0_IRQn);

	/* Greeting message */
	miniUSBPrint("\r\nRing buffer example\r\n");

	/* Loop forever */
	while (1) {
		ledOn(LED0);
		delay(MBED_TIMER0, 2500);

		miniUSBPrint("Reading buffer:\r\n");
		c = readValue();
		while (c != '0') {
			miniUSBPrint("Value: %c\r\n", c);
			c = readValue();
		}

		ledOff(LED0);
		delay(MBED_TIMER0, 2500);
	}

	return 0;
}

