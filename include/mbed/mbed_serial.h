/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#ifndef MBED_SERIAL_H
#define MBED_SERIAL_H

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

void setSerialBaudrate(uint8_t, uint32_t);
void initSerial(uint8_t);
uint32_t serialSend(uint8_t, uint8_t*, uint32_t);
uint32_t serialRecv(uint8_t, uint8_t*, uint32_t);
uint32_t recvReady(uint8_t);

#endif

