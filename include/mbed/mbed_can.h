/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#ifndef MBED_CAN_H
#define MBED_CAN_H

/* CANOpen COB Types */
#define CAN_COB_NMT		(0 << 7)
#define CAN_COB_SYNC		(1 << 7)
#define CAN_COB_TIMESTAMP	(2 << 7)
#define CAN_COB_EMERGENCY	(1 << 7)
#define CAN_COB_TPDO1		(3 << 7)
#define CAN_COB_RPDO1		(4 << 7)
#define CAN_COB_TPDO2		(5 << 7)
#define CAN_COB_RPDO2		(6 << 7)
#define CAN_COB_TPDO3		(7 << 7)
#define CAN_COB_RPDO3		(8 << 7)
#define CAN_COB_TPDO4		(9 << 7)
#define CAN_COB_RPDO4		(10 << 7)
#define CAN_COB_TSDO		(11 << 7)
#define CAN_COB_RSDO		(12 << 7)
#define CAN_COB_ERROR_CONTROL	(14 << 7)

/* CANOpen Network Management Commands */
#define CAN_NMT_RESET		0x81
#define CAN_NMT_START		1
#define CAN_NMT_STOP		2

#include "LPC17xx.h"
#include "lpc17xx_can.h"
#include "lpc17xx_pinsel.h"

void setCANBaudrate(uint8_t, uint32_t);
void initCAN(uint8_t);
uint8_t CANOpenSend(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t*);
uint8_t CANOpenRecv(uint8_t, uint8_t*, uint32_t*, uint8_t*);

#endif

