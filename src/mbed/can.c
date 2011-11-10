/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include <stdlib.h>

#include "mbed.h"

/* Baudrates */
static uint32_t _rate0;
static uint32_t _rate1;

/* CAN0 receive buffer */
volatile static CAN_MSG_Type _rxBuf0[CAN_BUFSIZE];
volatile static uint32_t _rxBuf0_ri;
volatile static uint32_t _rxBuf0_wi;

/* CAN0 transmit buffer */
volatile static CAN_MSG_Type _txBuf0[CAN_BUFSIZE];
volatile static uint32_t _txBuf0_ri;
volatile static uint32_t _txBuf0_wi;

/* CAN1 receive buffer */
volatile static CAN_MSG_Type _rxBuf1[CAN_BUFSIZE];
volatile static uint32_t _rxBuf1_ri;
volatile static uint32_t _rxBuf1_wi;

/* CAN1 transmit buffer */
volatile static CAN_MSG_Type _txBuf1[CAN_BUFSIZE];
volatile static uint32_t _txBuf1_ri;
volatile static uint32_t _txBuf1_wi;

static uint32_t _incrIndex(volatile const uint32_t);

void setCANBaudrate(uint8_t portNo, uint32_t baudrate) {
	switch (portNo) {
		case MBED_CAN0:
			_rate0 = baudrate;
			break;
		case MBED_CAN1:
			_rate1 = baudrate;
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
			CAN_Init(LPC_CAN1, _rate0);
			CAN_ModeConfig(LPC_CAN1, CAN_SELFTEST_MODE, ENABLE);

			/* Enable receive and transmit interrupts */
			CAN_IRQCmd(LPC_CAN1, CANINT_RIE, ENABLE);	/* Receive */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE1, ENABLE);	/* Transmit 1 */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE2, ENABLE);	/* Transmit 2 */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE3, ENABLE);	/* Transmit 3 */

			/* Initialize buffers */
			memset((void*)_rxBuf0, 0, sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_rxBuf0_ri = 0;
			_rxBuf0_wi = 0;
			memset((void*)_txBuf0, 0, sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_txBuf0_ri = 0;
			_txBuf0_wi = 0;

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
			CAN_Init(LPC_CAN2, _rate1);
			CAN_ModeConfig(LPC_CAN2, CAN_SELFTEST_MODE, ENABLE);

			/* Enable receive and transmit interrupts */
			CAN_IRQCmd(LPC_CAN2, CANINT_RIE, ENABLE);	/* Receive */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE1, ENABLE);	/* Transmit 1 */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE2, ENABLE);	/* Transmit 2 */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE3, ENABLE);	/* Transmit 3 */

			/* Initialize buffers */
			memset((void*)_rxBuf1, 0, sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_rxBuf1_ri = 0;
			_rxBuf1_wi = 0;
			memset((void*)_txBuf1, 0, sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_txBuf1_ri = 0;
			_txBuf1_wi = 0;

			/* Update status flags. */
			mbedStatus |= MBED_CAN1_INIT;

			break;
		default:
			return;
	}

	/* Bypass acceptance filter. */
	CAN_SetAFMode(LPC_CANAF, CAN_AccBP);

	/* Enable interrupts */
	NVIC_EnableIRQ(CAN_IRQn);
}

uint8_t CANOpenRecv(uint8_t portNo, uint8_t* nodeID, uint32_t* cobType, uint8_t* data) {
	CAN_MSG_Type msg;
	uint8_t i = 0;
	uint8_t r = 0;

	switch (portNo) {
		case MBED_CAN0:
			/* Wait while buffer is empty */
			while (_rxBuf0_ri == _rxBuf0_wi) ;

			/* Read message */
			NVIC_DisableIRQ(CAN_IRQn);
			msg = _rxBuf0[_rxBuf0_ri];
			_rxBuf0_ri = _incrIndex(_rxBuf0_ri);
			NVIC_EnableIRQ(CAN_IRQn);
			r = SUCCESS;

			break;
		case MBED_CAN1:
			/* Wait while buffer is empty */
			while (_rxBuf1_ri == _rxBuf1_wi) ;

			/* Read message */
			NVIC_DisableIRQ(CAN_IRQn);
			msg = _rxBuf1[_rxBuf1_ri];
			_rxBuf1_ri = _incrIndex(_rxBuf1_ri);
			NVIC_EnableIRQ(CAN_IRQn);
			r = SUCCESS;

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
			/* Try sending message, otherwise buffer it */
			if (CAN_SendMsg(LPC_CAN1, &msg) != SUCCESS) {
				if (_incrIndex(_txBuf0_wi) == _txBuf0_ri) {
					// Buffer is full
					r = ERROR;
				} else {
					NVIC_DisableIRQ(CAN_IRQn);
					_txBuf0[_txBuf0_wi] = msg;
					_txBuf0_wi = _incrIndex(_txBuf0_wi);
					NVIC_EnableIRQ(CAN_IRQn);
					r = SUCCESS;
				}
			} else {
				r = SUCCESS;
			}

			break;
		case MBED_CAN1:
			/* Try sending message, otherwise buffer it */
			if (CAN_SendMsg(LPC_CAN2, &msg) != SUCCESS) {
				if (_incrIndex(_txBuf1_wi) == _txBuf1_ri) {
					// Buffer is full
					r = ERROR;
				} else {
					NVIC_DisableIRQ(CAN_IRQn);
					_txBuf1[_txBuf1_wi] = msg;
					_txBuf1_wi = _incrIndex(_txBuf1_wi);
					NVIC_EnableIRQ(CAN_IRQn);
					r = SUCCESS;
				}
			} else {
				r = SUCCESS;
			}

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

void CAN_IRQHandler(void) {
	CAN_MSG_Type msg;
	uint32_t icrCAN0 = 0;
	uint32_t icrCAN1 = 0;

	/* Disable interrupts. */
	NVIC_DisableIRQ(CAN_IRQn);

	/* Process interrupt for MBED_CAN0. */
	if (mbedStatus & MBED_CAN0_INIT) {
		icrCAN0 = CAN_IntGetStatus(LPC_CAN1);

		/* Check if a message is received. */
		if (icrCAN0 & (1 << 0) ) {
			// Read message
			CAN_ReceiveMsg(LPC_CAN1, &msg);
			_rxBuf0[_rxBuf0_wi] = msg;
			_rxBuf0_wi = _incrIndex(_rxBuf0_wi);
		}

		/* Check if a message is sent. */
		if ( icrCAN0 & ((1 << 1) | (1 << 9) | (1 << 10)) ) {
			// At least 1 tx buffer is available, send message if available
			if (_txBuf1_ri != _txBuf1_wi) {
				msg = _txBuf0[_txBuf0_ri];
				_txBuf0_ri = _incrIndex(_txBuf0_ri);
				CAN_SendMsg(LPC_CAN1, &msg);
			}
		}
	}

	/* Process interrupt for MBED_CAN1. */
	if (mbedStatus & MBED_CAN1_INIT) {
		icrCAN1 = CAN_IntGetStatus(LPC_CAN2);

		/* Check if a message is received. */
		if (icrCAN1 & (1 << 0) ) {
			// Read message
			CAN_ReceiveMsg(LPC_CAN2, &msg);
			_rxBuf1[_rxBuf1_wi] = msg;
			_rxBuf1_wi = _incrIndex(_rxBuf1_wi);
		}
		
		/* Check if a message is sent. */
		if ( icrCAN1 & ((1 << 1) | (1 << 9) | (1 << 10)) ) {
			// At least 1 tx buffer is available, send message if available
			if (_txBuf1_ri != _txBuf1_wi) {
				msg = _txBuf1[_txBuf1_ri];
				_txBuf1_ri = _incrIndex(_txBuf1_ri);
				CAN_SendMsg(LPC_CAN2, &msg);
			}
		}
	}

	/* Enable interrupts. */
	NVIC_EnableIRQ(CAN_IRQn);
}

static uint32_t _incrIndex(volatile const uint32_t index) {
	if (index == (CAN_BUFSIZE - 1)) {
		return 0;
	} else {
		return index + 1;
	}
}

