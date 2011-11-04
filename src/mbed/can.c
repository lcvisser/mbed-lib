/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include <stdlib.h>

#include "mbed.h"

/* Baudrates */
static uint32_t _canRate0;
static uint32_t _canRate1;

/* CAN0 receive buffer */
static CAN_MSG_Type* _canRxBuf0_head;
static CAN_MSG_Type* _canRxBuf0_tail;
volatile static CAN_MSG_Type* _canRxBuf0_rp;
volatile static CAN_MSG_Type* _canRxBuf0_wp;

/* CAN0 transmit buffer */
static CAN_MSG_Type* _canTxBuf0_head;
static CAN_MSG_Type* _canTxBuf0_tail;
volatile static CAN_MSG_Type* _canTxBuf0_rp;
volatile static CAN_MSG_Type* _canTxBuf0_wp;

/* CAN1 receive buffer */
static CAN_MSG_Type* _canRxBuf1_head;
static CAN_MSG_Type* _canRxBuf1_tail;
volatile static CAN_MSG_Type* _canRxBuf1_rp;
volatile static CAN_MSG_Type* _canRxBuf1_wp;

/* CAN1 transmit buffer */
static CAN_MSG_Type* _canTxBuf1_head;
static CAN_MSG_Type* _canTxBuf1_tail;
volatile static CAN_MSG_Type* _canTxBuf1_rp;
volatile static CAN_MSG_Type* _canTxBuf1_wp;

static CAN_MSG_Type* _CANBufPtrIncrement(volatile CAN_MSG_Type* const, CAN_MSG_Type* const, CAN_MSG_Type* const);

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
			CAN_IRQCmd(LPC_CAN1, CANINT_RIE, ENABLE);	/* Receive */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE1, ENABLE);	/* Transmit 1 */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE2, ENABLE);	/* Transmit 2 */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE3, ENABLE);	/* Transmit 3 */

			/* Initialize buffers */
			_canRxBuf0_head = malloc(sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_canRxBuf0_tail = &_canRxBuf0_head[CAN_BUFSIZE - 1];
			_canRxBuf0_rp = _canRxBuf0_head;
			_canRxBuf0_wp = _canRxBuf0_head;

			_canTxBuf0_head = malloc(sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_canTxBuf0_tail = &_canTxBuf0_head[CAN_BUFSIZE - 1];
			_canTxBuf0_rp = _canTxBuf0_head;
			_canTxBuf0_wp = _canTxBuf0_head;

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
			CAN_IRQCmd(LPC_CAN2, CANINT_RIE, ENABLE);	/* Receive */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE1, ENABLE);	/* Transmit 1 */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE2, ENABLE);	/* Transmit 2 */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE3, ENABLE);	/* Transmit 3 */

			/* Initialize buffers */
			_canRxBuf1_head = malloc(sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_canRxBuf1_tail = &_canRxBuf1_head[CAN_BUFSIZE - 1];
			_canRxBuf1_rp = _canRxBuf1_head;
			_canRxBuf1_wp = _canRxBuf1_head;

			_canTxBuf1_head = malloc(sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_canTxBuf1_tail = &_canTxBuf1_head[CAN_BUFSIZE - 1];
			_canTxBuf1_rp = _canTxBuf1_head;
			_canTxBuf1_wp = _canTxBuf1_head;

			/* Update status flags. */
			mbedStatus |= MBED_CAN1_INIT;

			break;
		default:
			return;
	}

	/* Enable interrupts */
	NVIC_EnableIRQ(CAN_IRQn);
}

uint8_t CANOpenRecv(uint8_t portNo, uint8_t* nodeID, uint32_t* cobType, uint8_t* data) {
	CAN_MSG_Type msg;
	uint8_t i = 0;
	uint8_t r = 0;

	switch (portNo) {
		case MBED_CAN0:
			if (_canRxBuf0_rp == _canRxBuf0_wp) {
				// Buffer is empty
				r = ERROR;
			} else {
				NVIC_DisableIRQ(CAN_IRQn);
				memcpy((void*)&msg, (const void*)_canRxBuf0_rp, sizeof(CAN_MSG_Type));
				_canRxBuf0_rp = _CANBufPtrIncrement(_canRxBuf0_rp, _canRxBuf0_head, _canRxBuf0_tail);
				NVIC_EnableIRQ(CAN_IRQn);
				r = SUCCESS;
			}

			break;
		case MBED_CAN1:
			if (_canRxBuf1_rp == _canRxBuf1_wp) {
				// Buffer is empty
				r = ERROR;
			} else {
				NVIC_DisableIRQ(CAN_IRQn);
				memcpy((void*)&msg, (const void*)_canRxBuf1_rp, sizeof(CAN_MSG_Type));
				_canRxBuf1_rp = _CANBufPtrIncrement(_canRxBuf1_rp, _canRxBuf1_head, _canRxBuf1_tail);
				NVIC_EnableIRQ(CAN_IRQn);
				r = SUCCESS;
			}

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
			if (_CANBufPtrIncrement(_canTxBuf0_wp, _canTxBuf0_head, _canTxBuf0_tail) == _canTxBuf0_rp) {
				// Buffer is full
				r = ERROR;
			} else {
				NVIC_DisableIRQ(CAN_IRQn);
				memcpy((void*)_canTxBuf0_wp, (const void*)&msg, sizeof(CAN_MSG_Type));
				_canTxBuf0_wp = _CANBufPtrIncrement(_canTxBuf0_wp, _canTxBuf0_head, _canTxBuf0_tail);
				NVIC_EnableIRQ(CAN_IRQn);
				r = SUCCESS;
			}

			break;
		case MBED_CAN1:
			if (_CANBufPtrIncrement(_canTxBuf1_wp, _canTxBuf1_head, _canTxBuf1_tail) == _canTxBuf1_rp) {
				// Buffer is full
				r = ERROR;
			} else {
				NVIC_DisableIRQ(CAN_IRQn);
				memcpy((void*)_canTxBuf1_wp, (const void*)&msg, sizeof(CAN_MSG_Type));
				_canTxBuf1_wp = _CANBufPtrIncrement(_canTxBuf1_wp, _canTxBuf1_head, _canTxBuf1_tail);
				NVIC_EnableIRQ(CAN_IRQn);
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
	uint32_t icrCAN0 = CAN_IntGetStatus(LPC_CAN1);
	uint32_t icrCAN1 = CAN_IntGetStatus(LPC_CAN2);

	/* Check if a message is received. */
	if (icrCAN0 & (1 << 0) ) {
		// Read message
		NVIC_DisableIRQ(CAN_IRQn);
		CAN_ReceiveMsg(LPC_CAN1, &msg);
		memcpy((void*)_canRxBuf0_wp, (const void*)&msg, sizeof(CAN_MSG_Type));
		_canRxBuf0_wp = _CANBufPtrIncrement(_canRxBuf0_wp, _canRxBuf0_head, _canRxBuf0_tail);
		NVIC_EnableIRQ(CAN_IRQn);
	}
	if (icrCAN1 & (1 << 0) ) {
		// Read message
		NVIC_DisableIRQ(CAN_IRQn);
		CAN_ReceiveMsg(LPC_CAN2, &msg);
		memcpy((void*)_canRxBuf1_wp, (const void*)&msg, sizeof(CAN_MSG_Type));
		_canRxBuf1_wp = _CANBufPtrIncrement(_canRxBuf1_wp, _canRxBuf1_head, _canRxBuf1_tail);
		NVIC_EnableIRQ(CAN_IRQn);
	}
	
	/* Check if a message is sent. */
	if ( icrCAN0 & ((1 << 1) | (1 << 9) | (1 << 10)) ) {
		// At least 1 tx buffer is available, send message
		NVIC_DisableIRQ(CAN_IRQn);
		memcpy((void*)&msg, (const void*)_canTxBuf0_rp, sizeof(CAN_MSG_Type));
		_canTxBuf0_rp = _CANBufPtrIncrement(_canTxBuf0_rp, _canTxBuf0_head, _canTxBuf0_tail);
		CAN_SendMsg(LPC_CAN1, &msg);
		NVIC_EnableIRQ(CAN_IRQn);
	}
	if ( icrCAN1 & ((1 << 1) | (1 << 9) | (1 << 10)) ) {
		// At least 1 tx buffer is available, send message
		NVIC_DisableIRQ(CAN_IRQn);
		memcpy((void*)&msg, (const void*)_canTxBuf1_rp, sizeof(CAN_MSG_Type));
		_canTxBuf1_rp = _CANBufPtrIncrement(_canTxBuf1_rp, _canTxBuf1_head, _canTxBuf1_tail);
		CAN_SendMsg(LPC_CAN1, &msg);
		NVIC_EnableIRQ(CAN_IRQn);
	}
}

static CAN_MSG_Type* _CANBufPtrIncrement(volatile CAN_MSG_Type* const p, CAN_MSG_Type* const head, CAN_MSG_Type* const tail) {
	CAN_MSG_Type* np = NULL;

	if (p == tail) {
		np = head;
	} else {
		np = (CAN_MSG_Type*)p + sizeof(CAN_MSG_Type);
	}

	return np;
}
