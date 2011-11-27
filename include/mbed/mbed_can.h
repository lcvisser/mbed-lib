/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

/*!
 * \file
 * 
 * \brief Various definitions for the CANopen implementation.
 *
 * This file defines a basic number of objects and messages for the CANopen
 * implementation provided by mbed-lib, and it provides function definitions.
 */
#include "LPC17xx.h"
#include "lpc17xx_can.h"
#include "lpc17xx_pinsel.h"

#ifndef MBED_CAN_H
#define MBED_CAN_H	/*!< Header guard. */

/*! \defgroup cobs CANopen objects
 * These define numeric identifiers for a set of CANopen object types.
 * @{
 */
#define CAN_COB_NMT		(0 << 7)	/*!< Network management. */
#define CAN_COB_SYNC		(1 << 7)	/*!< Synchronization. */
#define CAN_COB_TIME		(2 << 7)	/*!< Timestamp. */
#define CAN_COB_EMCY		(1 << 7)	/*!< Emergency. */
#define CAN_COB_TPDO1		(3 << 7)	/*!< PDO1 transmit. */
#define CAN_COB_RPDO1		(4 << 7)	/*!< PDO1 receive. */
#define CAN_COB_TPDO2		(5 << 7)	/*!< PDO2 transmit. */
#define CAN_COB_RPDO2		(6 << 7)	/*!< PDO2 receive. */
#define CAN_COB_TPDO3		(7 << 7)	/*!< PDO3 transmit. */
#define CAN_COB_RPDO3		(8 << 7)	/*!< PDO3 receive. */
#define CAN_COB_TPDO4		(9 << 7)	/*!< PDO4 transmit. */
#define CAN_COB_RPDO4		(10 << 7)	/*!< PDO4 receive. */
#define CAN_COB_TSDO		(11 << 7)	/*!< SDO transmit. */
#define CAN_COB_RSDO		(12 << 7)	/*!< SDO receive. */
#define CAN_COB_ERROR_CONTROL	(14 << 7)	/*!< Error control. */
/*! @} */

/*! \defgroup nmt Network management commands
 *
 * CANOpen network management commands are used for node control.
 * @{
 */
#define CAN_NMT_START		0x01	/*!< Start node. */
#define CAN_NMT_STOP		0x02	/*!< Stop node. */
#define CAN_NMT_PREOP		0x80	/*!< Enter pre-operational state. */
#define CAN_NMT_RESET		0x81	/*!< Reset node. */
#define CAN_NMT_RSCOMM		0x82	/*!< Reset node communication. */
/* @} */

/*! CAN buffer size.
 * \sa can0buf
 * \sa can1buf
 */
#define CAN_BUFSIZE		256

/* Function defintions. */
void setCANBaudrate(uint8_t, uint32_t);
void initCAN(uint8_t);
uint8_t CANopenRecv(uint8_t, uint8_t*, uint32_t*, uint8_t*);
uint8_t CANopenSend(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t*);
void flushCANRxBuffer(uint8_t);
void flushCANTxBuffer(uint8_t);
void CAN_IRQHandler(void);

#endif

