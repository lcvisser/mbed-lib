/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

#ifndef MBED_MINI_USB_H
#define MBED_MINI_USB_H

#define TXBUFSIZE		1024

void setMiniUSBBaudrate(uint32_t);
void initMiniUSB(void);;
uint32_t miniUSBSend(uint8_t*, uint32_t);
uint32_t miniUSBRecv(uint8_t*, uint32_t);
uint32_t miniUSBRecvReady(void);
uint32_t miniUSBPrint(const char*, ...);

#endif

