/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"

/* Baudrates */
static uint32_t _serialRate0;
static uint32_t _serialRate1;
static uint32_t _serialRate2;

void setSerialBaudrate(uint8_t portNo, uint32_t baudrate) {
	switch (portNo) {
		case MBED_SERIAL0:
			_serialRate0 = baudrate;
			break;
		case MBED_SERIAL1:
			_serialRate1 = baudrate;
			break;
		case MBED_SERIAL2:
			_serialRate2 = baudrate;
			break;
		default:
			break;
	}
}

void initSerial(uint8_t portNo) {
	PINSEL_CFG_Type pinConfig;
	UART_CFG_Type uartConfig;
	UART_FIFO_CFG_Type uartFifoConfig;

	/* Configure pins. */
	pinConfig.OpenDrain = PINSEL_PINMODE_NORMAL;
	pinConfig.Pinmode = PINSEL_PINMODE_PULLUP;
	switch (portNo) {
		case MBED_SERIAL0:
			/* Check for initialization. */
			if ( mbedStatus & MBED_SERIAL0_INIT ) {
				return;
			}

			pinConfig.Funcnum = PINSEL_FUNC_1;
			pinConfig.Portnum = PINSEL_PORT_0;
			pinConfig.Pinnum = 15;		// DIP 13
			PINSEL_ConfigPin(&pinConfig);
			pinConfig.Pinnum = 16;		// DIP 14
			PINSEL_ConfigPin(&pinConfig);
			
			break;
		case MBED_SERIAL1:
			/* Check for initialization. */
			if ( mbedStatus & MBED_SERIAL1_INIT ) {
				return;
			}

			pinConfig.Funcnum = PINSEL_FUNC_1;
			pinConfig.Portnum = PINSEL_PORT_0;
			pinConfig.Pinnum = 11;		// DIP 27
			PINSEL_ConfigPin(&pinConfig);
			pinConfig.Pinnum = 10;		// DIP 28
			PINSEL_ConfigPin(&pinConfig);

			break;
		case MBED_SERIAL2:
			/* Check for initialization (CAN0 and SERIAL2 share DIP 9/10). */
			if ( (mbedStatus & MBED_SERIAL2_INIT) || (mbedStatus & MBED_CAN0_INIT) ) {
				return;
			}

			pinConfig.Funcnum = PINSEL_FUNC_2;
			pinConfig.Portnum = PINSEL_PORT_0;
			pinConfig.Pinnum = 0;		// DIP 9
			PINSEL_ConfigPin(&pinConfig);
			pinConfig.Pinnum = 1;		// DIP 10
			PINSEL_ConfigPin(&pinConfig);
			
			break;
		default:
			return;
	}

	/* Initialize UART. */
	UART_ConfigStructInit(&uartConfig);
	uartConfig.Parity = UART_PARITY_NONE;
	uartConfig.Databits = UART_DATABIT_8;
	uartConfig.Stopbits = UART_STOPBIT_1;
	switch (portNo) {
		case MBED_SERIAL0:
			uartConfig.Baud_rate = _serialRate0;
			UART_Init((LPC_UART_TypeDef*)LPC_UART1, &uartConfig);
			
			/* Initialize UART FIFO. */
			UART_FIFOConfigStructInit(&uartFifoConfig);
			UART_FIFOConfig((LPC_UART_TypeDef*)LPC_UART1, &uartFifoConfig);
	
			/* Enable transmit mode. */
			UART_TxCmd((LPC_UART_TypeDef*)LPC_UART1, ENABLE);

			/* Update status flags. */
			mbedStatus |= MBED_SERIAL0_INIT;
			
			break;
		case MBED_SERIAL1:
			uartConfig.Baud_rate = _serialRate1;
			UART_Init(LPC_UART2, &uartConfig);
			
			/* Initialize UART FIFO. */
			UART_FIFOConfigStructInit(&uartFifoConfig);
			UART_FIFOConfig(LPC_UART2, &uartFifoConfig);
	
			/* Enable transmit mode. */
			UART_TxCmd(LPC_UART2, ENABLE);

			/* Update status flags. */
			mbedStatus |= MBED_SERIAL1_INIT;
			
			break;
		case MBED_SERIAL2:
			uartConfig.Baud_rate = _serialRate2;
			UART_Init(LPC_UART3, &uartConfig);
			
			/* Initialize UART FIFO. */
			UART_FIFOConfigStructInit(&uartFifoConfig);
			UART_FIFOConfig(LPC_UART3, &uartFifoConfig);
	
			/* Enable transmit mode. */
			UART_TxCmd(LPC_UART3, ENABLE);

			/* Update status flags. */
			mbedStatus |= MBED_SERIAL2_INIT;
			
			break;
		default:
			break;
	}
}

uint32_t serialSend(uint8_t portNo, uint8_t* txbuf, uint32_t len) {
	uint32_t r = 0;

	switch (portNo) {
		case MBED_SERIAL0:
			r =  UART_Send((LPC_UART_TypeDef*)LPC_UART1, txbuf, len, BLOCKING);
			break;
		case MBED_SERIAL1:
			r =  UART_Send(LPC_UART2, txbuf, len, BLOCKING);
			break;
		case MBED_SERIAL2:
			r =  UART_Send(LPC_UART3, txbuf, len, BLOCKING);
			break;
		default:
			break;
	}

	return r;
}

uint32_t serialRecv(uint8_t portNo, uint8_t* rxbuf, uint32_t len) {
	uint32_t r = 0;

	switch (portNo) {
		case MBED_SERIAL0:
			r =  UART_Receive((LPC_UART_TypeDef*)LPC_UART1, rxbuf, len, BLOCKING);
			break;
		case MBED_SERIAL1:
			r =  UART_Receive(LPC_UART2, rxbuf, len, BLOCKING);
			break;
		case MBED_SERIAL2:
			r =  UART_Receive(LPC_UART3, rxbuf, len, BLOCKING);
			break;
		default:
			break;
	}

	return r;
}

uint32_t recvReady(uint8_t portNo) {
	uint32_t r = 0;

	switch (portNo) {
		case MBED_SERIAL0:
			r =  (UART_GetLineStatus((LPC_UART_TypeDef*)LPC_UART1) & UART_LINESTAT_RDR);
			break;
		case MBED_SERIAL1:
			r =  (UART_GetLineStatus(LPC_UART2) & UART_LINESTAT_RDR);
			break;
		case MBED_SERIAL2:
			r =  (UART_GetLineStatus(LPC_UART3) & UART_LINESTAT_RDR);
			break;
		default:
			break;
	}

	return r;
}

