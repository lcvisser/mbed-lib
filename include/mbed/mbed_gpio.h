/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "LPC17xx.h"
#include "lpc17xx_gpio.h"

#ifndef _MBED_GPIO_H
#define _MBED_GPIO_H

#define GPIO5	9	/* port 0 */
#define GPIO6	8	/* port 0 */
#define GPIO7	7	/* port 0 */
#define GPIO8	6	/* port 0 */
#define GPIO9	0	/* port 0 */
#define GPIO10	1	/* port 0 */
#define GPIO11	18	/* port 0 */
#define GPIO12	17	/* port 0 */
#define GPIO13	15	/* port 0 */
#define GPIO14	16	/* port 0 */
#define GPIO15	23	/* port 0 */
#define GPIO16	24	/* port 0 */
#define GPIO17	25	/* port 0 */
#define GPIO18	26	/* port 0 */
#define GPIO19	30	/* port 1 */
#define GPIO20	31	/* port 1 */
#define GPIO21	5	/* port 2 */
#define GPIO22	4	/* port 2 */
#define GPIO23	3	/* port 2 */
#define GPIO24	2	/* port 2 */
#define GPIO25	1	/* port 2 */
#define GPIO26	0	/* port 2 */
#define GPIO27	11	/* port 0 */
#define GPIO28	10	/* port 0 */
#define GPIO29	5	/* port 0 */
#define GPIO30	4	/* port 0 */

#define GP_LOW	0
#define GP_HIGH	1
#define GP_ERR	2	/* Pin is not configured */

/* GPIO configuration */
uint32_t _mbedGPICfg;
uint32_t _mbedGPOCfg;

void setGPInputCfg(uint32_t);
void setGPOutputCfg(uint32_t);
void initGPInputs(void);
void initGPOutputs(void);
void checkConflicts(void);
void initGPIO(uint32_t, uint32_t);
void GPIOSetVal(uint32_t, uint8_t);
uint8_t GPIOReadVal(uint32_t);

#endif

