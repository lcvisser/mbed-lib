/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

/*!
 * \file
 *
 * \brief Various definition for General Purpose Input/Output (GPIO).
 *
 * In this file are definitions for all pins on the MBED device. They can be
 * used as either input or output by adding them to the corresponding
 * configuration.
 */
#include "LPC17xx.h"
#include "lpc17xx_gpio.h"

#ifndef MBED_GPIO_H
#define MBED_GPIO_H	/*!< Header guard. */

/*! \defgroup gpiopins GPIO pin definitions
 * These define how the DIP connections of the MBED devices are connected.
 * @{
 */
#define GPIO5	9	/*!< DIP 5 is on position 9 of port 0. */
#define GPIO6	8	/*!< DIP 6 is on position 8 of port 0. */
#define GPIO7	7	/*!< DIP 7 is on position 7 of port 0. */
#define GPIO8	6	/*!< DIP 8 is on position 6 of port 0. */
#define GPIO9	0	/*!< DIP 9 is on position 0 of port 0. */
#define GPIO10	1	/*!< DIP 10 is on position 1 of port 0. */
#define GPIO11	18	/*!< DIP 11 is on position 18 of port 0. */
#define GPIO12	17	/*!< DIP 12 is on position 17 of port 0. */
#define GPIO13	15	/*!< DIP 13 is on position 15 of port 0. */
#define GPIO14	16	/*!< DIP 14 is on position 16 of port 0. */
#define GPIO15	23	/*!< DIP 15 is on position 23 of port 0. */
#define GPIO16	24	/*!< DIP 16 is on position 24 of port 0. */
#define GPIO17	25	/*!< DIP 17 is on position 25 of port 0. */
#define GPIO18	26	/*!< DIP 18 is on position 26 of port 0. */
#define GPIO19	30	/*!< DIP 19 is on position 30 of port 1. */
#define GPIO20	31	/*!< DIP 20 is on position 31 of port 1. */
#define GPIO21	5	/*!< DIP 21 is on position 5 of port 2. */
#define GPIO22	4	/*!< DIP 22 is on position 4 of port 2. */
#define GPIO23	3	/*!< DIP 23 is on position 3 of port 2. */
#define GPIO24	2	/*!< DIP 24 is on position 2 of port 2. */
#define GPIO25	1	/*!< DIP 25 is on position 1 of port 2. */
#define GPIO26	0	/*!< DIP 26 is on position 0 of port 2. */
#define GPIO27	11	/*!< DIP 27 is on position 11 of port 0. */
#define GPIO28	10	/*!< DIP 28 is on position 10 of port 0. */
#define GPIO29	5	/*!< DIP 29 is on position 5 of port 0. */
#define GPIO30	4	/*!< DIp 30 is on position 4 of port 0. */
/*! @} */

/*! \defgroup gpiolvl GPIO levels
 * Set and read values for GPIO ports.
 * \sa GPIOSetVal()
 * \sa GPIOReadVal()
 * @{
 */
#define GP_LOW	0	/*!< Low level (ground). */
#define GP_HIGH	1	/*!< High level (+3.3V)/ */
#define GP_ERR	2	/*!< Indicates that the pin is not configured. */
/*! @} */

/* Function defintions. */
void setGPInputCfg(uint32_t);
void setGPOutputCfg(uint32_t);
void initGPInputs(void);
void initGPOutputs(void);
void checkConflicts(void);
void initGPIO(uint32_t, uint32_t);
void GPIOSetVal(uint32_t, uint8_t);
uint8_t GPIOReadVal(uint32_t);

#endif

