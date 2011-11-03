/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"

/* Baudrates */
volatile static uint32_t _canRate0;
volatile static uint32_t _canRate1;

void setCANBaudrate(uint8_t portNo, uint32_t baudrate) {
	switch (portNo) {
		case MBED_CAN0:
			_canRate0 = baudrate;
			break;
		case MBED_CAN1:
			_canRate1 = baudrate;
			break;
		default:
			break;
	}
}

void initCAN(uint8_t portNo) {
	PINSEL_CFG_Type pinConfig;

	/* Configure pins. */
	pinConfig.OpenDrain = PINSEL_PINMODE_NORMAL;
	pinConfig.Pinmode = PINSEL_PINMODE_PULLUP;
	switch (portNo) {
		case MBED_CAN0:
			/* Check for initialization (CAN0 and SERIAL2 share DIP 9/10). */
			if ( (mbedStatus & MBED_CAN0_INIT) || (mbedStatus & MBED_SERIAL2_INIT) ) {
				return;
			}

			pinConfig.Funcnum = PINSEL_FUNC_1;
			pinConfig.Portnum = PINSEL_PORT_0;
			pinConfig.Pinnum = 0;		// DIP 9
			PINSEL_ConfigPin(&pinConfig);
			pinConfig.Pinnum = 1;		// DIP 10
			PINSEL_ConfigPin(&pinConfig);
			
			/* Initialize CAN. */
			CAN_Init(LPC_CAN1, _canRate0);
			CAN_ModeConfig(LPC_CAN1, CAN_SELFTEST_MODE, ENABLE);
			CAN_SetAFMode(LPC_CANAF, CAN_AccBP);

			/* Enable receive and transmit interrupts */
			CAN_IRQCmd(LPC_CAN1, CANINT_RIE);	/* Receive */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE1);	/* Transmit 1 */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE2);	/* Transmit 2 */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE3);	/* Transmit 3 */

			/* Update status flags. */
			mbedStatus |= MBED_CAN0_INIT;

			break;
		case MBED_CAN1:
			/* Check for initialization. */
			if ( mbedStatus & MBED_CAN1_INIT ) {
				return;
			}

			pinConfig.Funcnum = PINSEL_FUNC_2;
			pinConfig.Portnum = PINSEL_PORT_0;
			pinConfig.Pinnum = 4;		// DIP 30
			PINSEL_ConfigPin(&pinConfig);
			pinConfig.Pinnum = 5;		// DIP 29
			PINSEL_ConfigPin(&pinConfig);

			/* Initialize CAN. */
			CAN_Init(LPC_CAN2, _canRate1);
			CAN_ModeConfig(LPC_CAN2, CAN_SELFTEST_MODE, ENABLE);
			CAN_SetAFMode(LPC_CANAF, CAN_AccBP);

			/* Enable receive and transmit interrupts */
			CAN_IRQCmd(LPC_CAN2, CANINT_RIE);	/* Receive */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE1);	/* Transmit 1 */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE2);	/* Transmit 2 */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE3);	/* Transmit 3 */

			/* Update status flags. */
			mbedStatus |= MBED_CAN1_INIT;

			break;
		default:
			return;
	}
}

void CAN_IRQHandler(void) {
	__disable_irq();


	__enable_irq();
}

uint8_t CANOpenSend(uint8_t portNo, uint8_t nodeID, uint32_t cobType, uint8_t len, uint8_t* data) {
	CAN_MSG_Type msg;
	uint8_t i = 0;
	uint8_t r = 0;

	msg.id = (nodeID & 0x7f) | cobType;
	msg.format = STD_ID_FORMAT;
	msg.type = DATA_FRAME;

	/* Truncate data. */
	if (len > 8) {
		msg.len = 8;
	} else {
		msg.len = len;
	}

	if ( len <= 4 ) {
		for (i = 0; i < len; i++) {
			msg.dataA[i] = data[i];
		}
	} else {
		for (i = 0; i < 4; i++) {
			msg.dataA[i] = data[i];
			msg.dataB[i] = data[i + 4];
		}
	}
	
	switch (portNo) {
		case MBED_CAN0:
			r = CAN_SendMsg(LPC_CAN1, &msg);
			break;
		case MBED_CAN1:
			r = CAN_SendMsg(LPC_CAN2, &msg);
			break;
		default:
			r = ERROR;
			break;
	}

	if ( r == SUCCESS ) {
		return 0;
	} else {
		return 1;
	}
}

uint8_t CANOpenRecv(uint8_t portNo, uint8_t* nodeID, uint32_t* cobType, uint8_t* data) {
	CAN_MSG_Type msg;
	uint8_t i = 0;
	uint8_t r = 0;

	switch (portNo) {
		case MBED_CAN0:
			r = CAN_ReceiveMsg(LPC_CAN1, &msg);
			break;
		case MBED_CAN1:
			r = CAN_ReceiveMsg(LPC_CAN2, &msg);
			break;
		default:
			r = ERROR;
			break;
	}

	if ( r == SUCCESS ) {
		/* Process message */
		*nodeID = msg.id & 0x7f;
		*cobType = msg.id & (~0x7f);
		if ( msg.len <= 4 ) {
			for (i = 0; i < msg.len; i++) {
				data[i] = msg.dataA[i];
			}
		} else {
			for (i = 0; i < 4; i++) {
				data[i] = msg.dataA[i];
				data[i + 4] = msg.dataB[i];
			}
		}

		return 0;
	} else {
		return 1;
	}
}

