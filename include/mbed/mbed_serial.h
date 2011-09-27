/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#ifndef _SERIAL0_BAUDRATE
#define _SERIAL0_BAUDRATE	9600
#endif

#ifndef _SERIAL1_BAUDRATE
#define _SERIAL1_BAUDRATE	9600
#endif

#ifndef _SERIAL2_BAUDRATE
#define _SERIAL2_BAUDRATE	9600
#endif

#ifndef _MBED_SERIAL_H
#define _MBED_SERIAL_H

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

void initSerial(uint8_t, uint32_t);
uint32_t serialSend(uint8_t, uint8_t*, uint32_t);
uint32_t serialRecv(uint8_t, uint8_t*, uint32_t);

#endif

