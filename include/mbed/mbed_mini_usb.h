/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#ifndef _MINI_USB_BAUDRATE
#define _MINI_USB_BAUDRATE	115200
#endif

#ifndef _MBED_MINI_USB_H
#define _MBED_MINI_USB_H

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

void initMiniUSB(uint32_t);
uint32_t miniUSBSend(uint8_t*, uint32_t);
uint32_t miniUSBRecv(uint8_t*, uint32_t);

#endif

