/* Copyright (c) 2011 Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#ifndef _UTIL_H
#define _UTIL_H

#include "LPC17xx.h"

void SysTick_Handler(void);
void initSys(void);
void wait(uint32_t);

#endif

