/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#ifndef _TIMER0_PS
#define _TIMER0_PS	1000
#endif

#ifndef _TIMER1_PS
#define _TIMER1_PS	1000
#endif

#ifndef _TIMER2_PS
#define _TIMER2_PS	1000
#endif

#ifndef _TIMER3_PS
#define _TIMER3_PS	1000
#endif

#ifndef _MBED_TIMER_H
#define _MBED_TIMER_H

#include "LPC17xx.h"
#include "lpc17xx_timer.h"

void initTimer(uint8_t, uint32_t);
void startTimer(uint8_t);
void stopTimer(uint8_t);
void resetTimer(uint8_t);
uint32_t getTimerVal(uint8_t);
void delay(uint8_t, uint32_t);

#endif

