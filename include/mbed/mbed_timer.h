/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "LPC17xx.h"
#include "lpc17xx_timer.h"

#ifndef MBED_TIMER_H
#define MBED_TIMER_H

void setTimerPrescale(uint8_t, uint32_t);
void initTimer(uint8_t);
void startTimer(uint8_t);
void stopTimer(uint8_t);
void resetTimer(uint8_t);
uint32_t getTimerVal(uint8_t);
void delay(uint8_t, uint32_t);

#endif

