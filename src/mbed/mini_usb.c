/* Copyright (c) 2011 Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mini_usb.h"

void initMiniUSB(void) {
	PINSEL_CFG_Type pinConfig;
	UART_CFG_Type uartConfig;
	UART_FIFO_CFG_Type uartFifoConfig;

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
	UART_Init(LPC_UART0, &uartConfig);
	UART_FIFOConfigStructInit(&uartFifoConfig);
	UART_FIFOConfig(LPC_UART0, &uartFifoConfig);
	UART_TxCmd(LPC_UART0, ENABLE);
}

