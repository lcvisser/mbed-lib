/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"

void initMiniUSB(uint32_t baudrate) {
	PINSEL_CFG_Type pinConfig;
	UART_CFG_Type uartConfig;
	UART_FIFO_CFG_Type uartFifoConfig;

	/* Check for initialization. */
	if ( mbedStatus & MBED_MUSB_INIT ) {
		return;
	}

	/* Configure pins. */
	pinConfig.Funcnum = PINSEL_FUNC_1;
	pinConfig.OpenDrain = PINSEL_PINMODE_NORMAL;
	pinConfig.Pinmode = PINSEL_PINMODE_PULLUP;
	pinConfig.Portnum = PINSEL_PORT_0;
	pinConfig.Pinnum = 2;		// TGT_SBL_TXD
	PINSEL_ConfigPin(&pinConfig);
	pinConfig.Pinnum = 3;		// TGT_SBL_RXD
	PINSEL_ConfigPin(&pinConfig);

	/* Initialize UART. */
	UART_ConfigStructInit(&uartConfig);
	uartConfig.Baud_rate = baudrate;
	uartConfig.Parity = UART_PARITY_NONE;
	uartConfig.Databits = UART_DATABIT_8;
	uartConfig.Stopbits = UART_STOPBIT_1;
	UART_Init(LPC_UART0, &uartConfig);

	/* Initialize UART FIFO. */
	UART_FIFOConfigStructInit(&uartFifoConfig);
	UART_FIFOConfig(LPC_UART0, &uartFifoConfig);
	
	/* Enable transmit mode. */
	UART_TxCmd(LPC_UART0, ENABLE);

	/* Update status flags. */
	mbedStatus |= MBED_MUSB_INIT;
}

uint32_t miniUSBSend(uint8_t* txbuf, uint32_t len) {
	return UART_Send(LPC_UART0, txbuf, len, BLOCKING);
}

uint32_t miniUSBRecv(uint8_t* rxbuf, uint32_t len) {
	return UART_Receive(LPC_UART0, rxbuf, len, NONE_BLOCKING);
}

uint32_t miniUSBRecvReady(void) {
	return UART_GetLineStatus(LPC_UART0) & UART_LINESTAT_RDR;
}

uint32_t miniUSBPrint(const char* format, ...) {
	char txbuf[TXBUFSIZE] = {'\0'};
	va_list args;

	va_start(args, format);
	vsnprintf(txbuf, TXBUFSIZE, format, args);
	va_end(args);

	return miniUSBSend((uint8_t*)txbuf, (uint32_t)strlen(txbuf));
}
	
