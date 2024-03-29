/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include <stdlib.h>

#include "mbed.h"

/*! \defgroup canrates CAN baudrates
 * Baudrates for the CAN interfaces. These are set via \ref setCANBaudrate().
 * @{
 */
static uint32_t _rate0;		/*!< Baudrate for MBED_CAN0. */
static uint32_t _rate1;		/*!< Baudrate for MBED_CAN1. */
/*! @} */

/*! \defgroup can0buf MBED_CAN0 buffers
 * Receive and transmit buffers for the MBED_CAN0 interface.
 * @{
 */
volatile static CAN_MSG_Type _rxBuf0[CAN_BUFSIZE];	/*!< Receive buffer for MBED_CAN0. */
volatile static uint32_t _rxBuf0_ri;			/*!< MBED_CAN0 receive buffer read index. */
volatile static uint32_t _rxBuf0_wi;			/*!< MBED_CAN0 receive buffer write index. */

volatile static CAN_MSG_Type _txBuf0[CAN_BUFSIZE];	/*!< Transmit buffer for MBED_CAN0. */
volatile static uint32_t _txBuf0_ri;			/*!< MBED_CAN0 transmit buffer read index. */
volatile static uint32_t _txBuf0_wi;			/*!< MBED_CAN0 transmit buffer write index. */
/*! @} */

/*! \defgroup can1buf MBED_CAN1 buffers
 * Receive and transmit buffers for the MBED_CAN0 interface.
 * @{
 */
volatile static CAN_MSG_Type _rxBuf1[CAN_BUFSIZE];	/*!< Receive buffer for MBED_CAN1. */
volatile static uint32_t _rxBuf1_ri;			/*!< MBED_CAN1 receive buffer read index. */
volatile static uint32_t _rxBuf1_wi;			/*!< MBED_CAN1 receive buffer write index. */

volatile static CAN_MSG_Type _txBuf1[CAN_BUFSIZE];	/*!< Transmit buffer for MBED_CAN1. */
volatile static uint32_t _txBuf1_ri;			/*!< MBED_CAN1 transmit buffer read index. */
volatile static uint32_t _txBuf1_wi;			/*!< MBED_CAN1 transmit buffer write index. */
/*! @} */

static uint32_t _incrIndex(volatile const uint32_t);

/*! \brief Baudrate configuration function.
 *
 * This function sets the baudrates for the MBED_CAN0 and MBED_CAN1 devices.
 * Call this function before calling \ref initSys().
 * \param portNo 	CAN interface to set the baudrate for. Should be
 *			MBED_CAN0 or MBED_CAN1.
 * \param baudrate	Desired baudrate, in bits per second.
 */
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

/*! \brief CAN initialization function.
 *
 * Initalizes the CAN interface. This function is called from \ref initSys(),
 * only call this function if you know what you are doing.
 * \param portNo	CAN interface to be initialized. Should be MBED_CAN0 or
 *			MBED_CAN1.
 *
 * \sa initSys()
 */
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
			pinConfig.Pinnum = 0;		/* DIP 9 */
			PINSEL_ConfigPin(&pinConfig);
			pinConfig.Pinnum = 1;		/* DIP 10 */
			PINSEL_ConfigPin(&pinConfig);
			
			/* Initialize CAN. */
			CAN_Init(LPC_CAN1, _rate0);
			CAN_ModeConfig(LPC_CAN1, CAN_SELFTEST_MODE, ENABLE);

			/* Enable receive and transmit interrupts. */
			CAN_IRQCmd(LPC_CAN1, CANINT_RIE, ENABLE);	/* Receive */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE1, ENABLE);	/* Transmit 1 */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE2, ENABLE);	/* Transmit 2 */
			CAN_IRQCmd(LPC_CAN1, CANINT_TIE3, ENABLE);	/* Transmit 3 */

			/* Initialize buffers. */
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
			if (mbedStatus & MBED_CAN1_INIT) {
				return;
			}

			pinConfig.Funcnum = PINSEL_FUNC_2;
			pinConfig.Portnum = PINSEL_PORT_0;
			pinConfig.Pinnum = 4;		/* DIP 30 */
			PINSEL_ConfigPin(&pinConfig);
			pinConfig.Pinnum = 5;		/* DIP 29 */
			PINSEL_ConfigPin(&pinConfig);

			/* Initialize CAN. */
			CAN_Init(LPC_CAN2, _rate1);
			CAN_ModeConfig(LPC_CAN2, CAN_SELFTEST_MODE, ENABLE);

			/* Enable receive and transmit interrupts. */
			CAN_IRQCmd(LPC_CAN2, CANINT_RIE, ENABLE);	/* Receive */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE1, ENABLE);	/* Transmit 1 */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE2, ENABLE);	/* Transmit 2 */
			CAN_IRQCmd(LPC_CAN2, CANINT_TIE3, ENABLE);	/* Transmit 3 */

			/* Initialize buffers. */
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

	/* Enable interrupts. */
	NVIC_EnableIRQ(CAN_IRQn);
}

/*! \brief Receive a CAN message via CANopen protocol.
 *
 * This routine reads an availabe message from the CAN receive buffer, if
 * available.
 * \param portNo	CAN interface to read from. Should be MBED_CAN0 or
 *			MBED_CAN1.
 * \param nodeID	Address of variable to store the CAN device ID that sent
 *			the message.
 * \param cobType	Address of variable to store the COB type of the
 *			message.
 * \param data		Pointer to data storage.
 *
 * \returns 0 if a message was successfully read, or an integer larger than 0
 *          when no message was available.
 *
 * \sa CANopenSend()
 * \sa cobs
 */
uint8_t CANopenRecv(uint8_t portNo, uint8_t* nodeID, uint32_t* cobType, uint8_t* data) {
	CAN_MSG_Type msg;
	uint8_t i = 0;
	uint8_t r = 0;

	NVIC_SetPendingIRQ(CAN_IRQn);
	switch (portNo) {
		case MBED_CAN0:
			/* Check if buffer is empty. */
			if (_rxBuf0_ri == _rxBuf0_wi) {
				r = ERROR;
			} else {
				/* Read message. */
				msg = _rxBuf0[_rxBuf0_ri];
				_rxBuf0_ri = _incrIndex(_rxBuf0_ri);
				r = SUCCESS;
			}

			break;
		case MBED_CAN1:
			/* Check if buffer is empty. */
			if (_rxBuf1_ri == _rxBuf1_wi) {
				r = ERROR;
			} else {
				/* Read message. */
				msg = _rxBuf1[_rxBuf1_ri];
				_rxBuf1_ri = _incrIndex(_rxBuf1_ri);
				r = SUCCESS;
			}

			break;
		default:
			r = ERROR;
			break;
	}
	NVIC_ClearPendingIRQ(CAN_IRQn);

	if (r == SUCCESS) {
		/* Process message. */
		*nodeID = msg.id & 0x7f;
		*cobType = msg.id & (~0x7f);
		if (msg.len <= 4) {
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

/*! \brief Send a CAN message via CANopen protocol.
 *
 * This routine sends a message via the CAN interface. If the message could not
 * be sent (because the internal transmit buffers are full), the message is
 * buffered and sent when when of the internal transmit buffers becomes
 * availble.
 * \param portNo	CAN interface to send on. Should be MBED_CAN0 or
 *			MBED_CAN1.
 * \param nodeID	ID of the CAN device the message should be sent to.
 * \param cobType	COB type of the message.
 * \param len		Message length.
 * \param data		Data to be sent. The total number of bytes that will be
 *			sent depends on the provided message length, but will
 *			never be more than eight bytes.
 *
 * \returns 0 if a message was successfully sent or buffered, or an integer
 *          larger than 0 when both sending and buffering failed.
 *
 * \sa CANopenRecv()
 * \sa cobs
 */
uint8_t CANopenSend(uint8_t portNo, uint8_t nodeID, uint32_t cobType, uint8_t len, uint8_t* data) {
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

	if (len <= 4) {
		for (i = 0; i < len; i++) {
			msg.dataA[i] = data[i];
		}
	} else {
		for (i = 0; i < 4; i++) {
			msg.dataA[i] = data[i];
			msg.dataB[i] = data[i + 4];
		}
	}
	
	NVIC_SetPendingIRQ(CAN_IRQn);
	switch (portNo) {
		case MBED_CAN0:
			/* Try sending message, otherwise buffer it. */
			if (CAN_SendMsg(LPC_CAN1, &msg) != SUCCESS) {
				if (_incrIndex(_txBuf0_wi) == _txBuf0_ri) {
					/* Buffer is full. */
					r = ERROR;
				} else {
					_txBuf0[_txBuf0_wi] = msg;
					_txBuf0_wi = _incrIndex(_txBuf0_wi);
					r = SUCCESS;
				}
			} else {
				r = SUCCESS;
			}

			break;
		case MBED_CAN1:
			/* Try sending message, otherwise buffer it. */
			if (CAN_SendMsg(LPC_CAN2, &msg) != SUCCESS) {
				if (_incrIndex(_txBuf1_wi) == _txBuf1_ri) {
					/* Buffer is full. */
					r = ERROR;
				} else {
					_txBuf1[_txBuf1_wi] = msg;
					_txBuf1_wi = _incrIndex(_txBuf1_wi);
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
	NVIC_ClearPendingIRQ(CAN_IRQn);

	if (r == SUCCESS) {
		return 0;
	} else {
		return 1;
	}
}

/*! \brief Flush CAN receive buffers.
 *
 * This routine flushes the CAN receive buffer by discarding all messages.
 * \param portNo	CAN interface of which the buffer should be flushed.
 *			Should be MBED_CAN0 or MBED_CAN1.
 *
 * \sa flushCANTxBuffer()
 */
void flushCANRxBuffer(uint8_t portNo) {
	NVIC_SetPendingIRQ(CAN_IRQn);
	switch (portNo) {
		case MBED_CAN0:
			memset((void*)_rxBuf0, 0, sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_rxBuf0_ri = 0;
			_rxBuf0_wi = 0;
			break;
		case MBED_CAN1:
			memset((void*)_rxBuf1, 0, sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_rxBuf1_ri = 0;
			_rxBuf1_wi = 0;
			break;
		default:
			break;
	}
	NVIC_ClearPendingIRQ(CAN_IRQn);
}

/*! \brief Flush CAN transmit buffers.
 *
 * This routine flushes the CAN transmit buffer by discarding all messages.
 * \param portNo	CAN interface of which the buffer should be flushed.
 *			Should be MBED_CAN0 or MBED_CAN1.
 *
 * \sa flushCANRxBuffer()
 */
void flushCANTxBuffer(uint8_t portNo) {
	NVIC_SetPendingIRQ(CAN_IRQn);
	switch (portNo) {
		case MBED_CAN0:
			memset((void*)_txBuf0, 0, sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_txBuf0_ri = 0;
			_txBuf0_wi = 0;
			break;
		case MBED_CAN1:
			memset((void*)_txBuf1, 0, sizeof(CAN_MSG_Type[CAN_BUFSIZE]));
			_txBuf1_ri = 0;
			_txBuf1_wi = 0;
			break;
		default:
			break;
	}
	NVIC_ClearPendingIRQ(CAN_IRQn);
}

/*! \brief CAN IRQ handler.
 *
 * This routine is called when either of the CAN devices raises an interrupt. Do
 * no call this routine yourself.
 */
void CAN_IRQHandler(void) {
	CAN_MSG_Type msg;
	uint32_t icrCAN0 = 0;
	uint32_t icrCAN1 = 0;

	/* Process interrupts for MBED_CAN0. */
	if (mbedStatus & MBED_CAN0_INIT) {
		icrCAN0 = CAN_IntGetStatus(LPC_CAN1);

		/* Check if a message is received. */
		if ( icrCAN0 & (1 << 0) ) {
			/* Read message and store it in receive buffer. */
			if (_incrIndex(_rxBuf0_wi) != _rxBuf0_ri) {
				/* There is space left in the receive buffer. */
				CAN_ReceiveMsg(LPC_CAN1, &msg);
				_rxBuf0[_rxBuf0_wi] = msg;
				_rxBuf0_wi = _incrIndex(_rxBuf0_wi);
			}
		}

		/* Check if a message is sent. */
		if ( icrCAN0 & ((1 << 1) | (1 << 9) | (1 << 10)) ) {
			/* At least one transmit buffer is available for sending. */
			if (_txBuf0_ri != _txBuf0_wi) {
				/* There is at least one message pending in the transmit buffer. */
				msg = _txBuf0[_txBuf0_ri];
				_txBuf0_ri = _incrIndex(_txBuf0_ri);
				while (CAN_SendMsg(LPC_CAN1, &msg) != SUCCESS) ;
			}
		}
	}

	/* Process interrupt for MBED_CAN1. */
	if (mbedStatus & MBED_CAN1_INIT) {
		icrCAN1 = CAN_IntGetStatus(LPC_CAN2);

		/* Check if a message is received. */
		if ( icrCAN1 & (1 << 0) ) {
			/* Read message and store it in receive buffer. */
			if (_incrIndex(_rxBuf1_wi) != _rxBuf1_ri) {
				/* There is space left in the receive buffer. */
				CAN_ReceiveMsg(LPC_CAN2, &msg);
				_rxBuf1[_rxBuf1_wi] = msg;
				_rxBuf1_wi = _incrIndex(_rxBuf1_wi);
			}
		}
		
		/* Check if a message is sent. */
		if ( icrCAN1 & ((1 << 1) | (1 << 9) | (1 << 10)) ) {
			/* At least one transmit buffer is available for sending. */
			if (_txBuf1_ri != _txBuf1_wi) {
				/* There is at least one message pending in the transmit buffer. */
				msg = _txBuf1[_txBuf1_ri];
				_txBuf1_ri = _incrIndex(_txBuf1_ri);
				while (CAN_SendMsg(LPC_CAN2, &msg) != SUCCESS) ;
			}
		}
	}
}

static uint32_t _incrIndex(volatile const uint32_t index) {
	if (index == (CAN_BUFSIZE - 1)) {
		return 0;
	} else {
		return index + 1;
	}
}

