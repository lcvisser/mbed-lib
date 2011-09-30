/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include "mbed.h"

extern uint32_t _mbedGPICfg;
extern uint32_t _mbedGPOCfg;

void setGPInputCfg(uint32_t config) {
	_mbedGPICfg = config;
}

void setGPOutputCfg(uint32_t config) {
	_mbedGPOCfg = config;
}

void initGPInputs() {
	/* Check for initialization. */
	if (mbedStatus & MBED_GPI_INIT) {
		return;
	}

	checkConflicts();
	initGPIO(INIT_GPI, _mbedGPICfg);

	/* Update status flags. */
	mbedStatus |= MBED_GPI_INIT;			
}

void initGPOutputs() {
	/* Check for initialization. */
	if (mbedStatus & MBED_GPO_INIT) {
		return;
	}

	checkConflicts();
	initGPIO(INIT_GPO, _mbedGPOCfg);

	/* Update status flags. */
	mbedStatus |= MBED_GPO_INIT;		
}

void checkConflicts() {
	/* DIP 9/10 conflicts with CAN0 */
	if (mbedStatus & MBED_CAN0_INIT) {
		_mbedGPICfg &= (~MBED_GPIO9);
		_mbedGPICfg &= (~MBED_GPIO10);
		_mbedGPOCfg &= (~MBED_GPIO9);
		_mbedGPOCfg &= (~MBED_GPIO10);
	}

	/* DIP 29/30 conflicts with CAN1 */
	if (mbedStatus & MBED_CAN1_INIT) {
		_mbedGPICfg &= (~MBED_GPIO29);
		_mbedGPICfg &= (~MBED_GPIO30);
		_mbedGPOCfg &= (~MBED_GPIO29);
		_mbedGPOCfg &= (~MBED_GPIO30);
	}

	/* DIP 13/14 conflicts with SERIAL0 */
	if (mbedStatus & MBED_SERIAL0_INIT) {
		_mbedGPICfg &= (~MBED_GPIO13);
		_mbedGPICfg &= (~MBED_GPIO14);
		_mbedGPOCfg &= (~MBED_GPIO13);
		_mbedGPOCfg &= (~MBED_GPIO14);
	}

	/* DIP 27/128 conflicts with SERIAL1 */
	if (mbedStatus & MBED_SERIAL1_INIT) {
		_mbedGPICfg &= (~MBED_GPIO27);
		_mbedGPICfg &= (~MBED_GPIO28);
		_mbedGPOCfg &= (~MBED_GPIO27);
		_mbedGPOCfg &= (~MBED_GPIO28);
	}

	/* DIP 9/10 conflicts with SERIAL2 */
	if (mbedStatus & MBED_SERIAL2_INIT) {
		_mbedGPICfg &= (~MBED_GPIO9);
		_mbedGPICfg &= (~MBED_GPIO10);
		_mbedGPOCfg &= (~MBED_GPIO9);
		_mbedGPOCfg &= (~MBED_GPIO10);
	}
}

void initGPIO(uint32_t mode, uint32_t gpioConfig) {
	PINSEL_CFG_Type pinConfig;
	uint8_t p;
	uint32_t pin;
	uint32_t portPins0 = 0;
	uint32_t portPins1 = 0;
	uint32_t portPins2 = 0;

	/* Configure pins */
	pinConfig.OpenDrain = PINSEL_PINMODE_NORMAL;
	pinConfig.Pinmode = PINSEL_PINMODE_PULLUP;
	pinConfig.Funcnum = PINSEL_FUNC_0;

	for (p = 1; p < 27; p++) {
		pin = (1 << p) & gpioConfig;
		switch (pin) {
			case MBED_GPIO5:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO5;	// DIP 5
				portPins0 |= (1 << GPIO5);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO6:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO6;	// DIP 6
				portPins0 |= (1 << GPIO6);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO7:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO7;	// DIP 7
				portPins0 |= (1 << GPIO7);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO8:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO8;	// DIP 8
				portPins0 |= (1 << GPIO8);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO9:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO9;	// DIP 9
				portPins0 |= (1 << GPIO9);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO10:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO10;	// DIP 10
				portPins0 |= (1 << GPIO10);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO11:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO11;	// DIP 11
				portPins0 |= (1 << GPIO11);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO12:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO12;	// DIP 12
				portPins0 |= (1 << GPIO12);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO13:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO13;	// DIP 13
				portPins0 |= (1 << GPIO13);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO14:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO14;	// DIP 14
				portPins0 |= (1 << GPIO14);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO15:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO15;	// DIP 15
				portPins0 |= (1 << GPIO15);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO16:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO16;	// DIP 16
				portPins0 |= (1 << GPIO16);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO17:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO17;	// DIP 17
				portPins0 |= (1 << GPIO17);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO18:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO18;	// DIP 18
				portPins0 |= (1 << GPIO18);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO19:
				pinConfig.Portnum = PINSEL_PORT_1;
				pinConfig.Pinnum = GPIO19;	// DIP 19
				portPins1 |= (1 << GPIO19);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO20:
				pinConfig.Portnum = PINSEL_PORT_1;
				pinConfig.Pinnum = GPIO20;	// DIP 20
				portPins1 |= (1 << GPIO20);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO21:
				pinConfig.Portnum = PINSEL_PORT_2;
				pinConfig.Pinnum = GPIO21;	// DIP 21
				portPins2 |= (1 << GPIO21);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO22:
				pinConfig.Portnum = PINSEL_PORT_2;
				pinConfig.Pinnum = GPIO22;	// DIP 22
				portPins2 |= (1 << GPIO22);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO23:
				pinConfig.Portnum = PINSEL_PORT_2;
				pinConfig.Pinnum = GPIO23;	// DIP 23
				portPins2 |= (1 << GPIO23);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO24:
				pinConfig.Portnum = PINSEL_PORT_2;
				pinConfig.Pinnum = GPIO24;	// DIP 24
				portPins2 |= (1 << GPIO24);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO25:
				pinConfig.Portnum = PINSEL_PORT_2;
				pinConfig.Pinnum = GPIO25;	// DIP 25
				portPins2 |= (1 << GPIO25);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO26:
				pinConfig.Portnum = PINSEL_PORT_2;
				pinConfig.Pinnum = GPIO26;	// DIP 26
				portPins2 |= (1 << GPIO26);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO27:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO27;	// DIP 27
				portPins0 |= (1 << GPIO27);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO28:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO28;	// DIP 28
				portPins0 |= (1 << GPIO28);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO29:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO29;	// DIP 29
				portPins0 |= (1 << GPIO29);
				PINSEL_ConfigPin(&pinConfig);
				break;
			case MBED_GPIO30:
				pinConfig.Portnum = PINSEL_PORT_0;
				pinConfig.Pinnum = GPIO30;	// DIP 30
				portPins0 |= (1 << GPIO30);
				PINSEL_ConfigPin(&pinConfig);
				break;
			default:
				break;
		}

	}

	/* Configure GPIO pins. */
	switch (mode) {
		case INIT_GPI:
			/* Configure pins as inputs. */
			GPIO_SetDir(0, portPins0, 0);
			GPIO_SetDir(1, portPins1, 0);
			GPIO_SetDir(2, portPins2, 0);

			break;
		case INIT_GPO:
			/* Configure pins as outputs. */
			GPIO_SetDir(0, portPins0, 1);
			GPIO_SetDir(1, portPins1, 1);
			GPIO_SetDir(2, portPins2, 1);

			/* Clear output values. */
			GPIO_ClearValue(0, portPins0);
			GPIO_ClearValue(1, portPins1);
			GPIO_ClearValue(2, portPins2);

			break;
		default:
			break;
	}
}

void GPIOSetVal(uint32_t pin, uint8_t val) {
	uint8_t portNo;
	uint32_t pinNo;

	if (_mbedGPOCfg & pin) {
		if (MBED_GPIO_P0 & pin) {
			portNo = 0;
		} else if (MBED_GPIO_P1 & pin) {
			portNo = 1;
		} else if (MBED_GPIO_P2 & pin) {
			portNo = 2;
		} else {
			return;
		}

		switch (pin) {
			case MBED_GPIO5:	pinNo = (1 << GPIO5);	break;
			case MBED_GPIO6:	pinNo = (1 << GPIO6);	break;
			case MBED_GPIO7:	pinNo = (1 << GPIO7);	break;
			case MBED_GPIO8:	pinNo = (1 << GPIO8);	break;
			case MBED_GPIO9:	pinNo = (1 << GPIO9);	break;
			case MBED_GPIO10:	pinNo = (1 << GPIO10);	break;
			case MBED_GPIO11:	pinNo = (1 << GPIO11);	break;
			case MBED_GPIO12:	pinNo = (1 << GPIO12);	break;
			case MBED_GPIO13:	pinNo = (1 << GPIO13);	break;
			case MBED_GPIO14:	pinNo = (1 << GPIO14);	break;
			case MBED_GPIO15:	pinNo = (1 << GPIO15);	break;
			case MBED_GPIO16:	pinNo = (1 << GPIO16);	break;
			case MBED_GPIO17:	pinNo = (1 << GPIO17);	break;
			case MBED_GPIO18:	pinNo = (1 << GPIO18);	break;
			case MBED_GPIO19:	pinNo = (1 << GPIO19);	break;
			case MBED_GPIO20:	pinNo = (1 << GPIO20);	break;
			case MBED_GPIO21:	pinNo = (1 << GPIO21);	break;
			case MBED_GPIO22:	pinNo = (1 << GPIO22);	break;
			case MBED_GPIO23:	pinNo = (1 << GPIO23);	break;
			case MBED_GPIO24:	pinNo = (1 << GPIO24);	break;
			case MBED_GPIO25:	pinNo = (1 << GPIO25);	break;
			case MBED_GPIO26:	pinNo = (1 << GPIO26);	break;
			case MBED_GPIO27:	pinNo = (1 << GPIO27);	break;
			case MBED_GPIO28:	pinNo = (1 << GPIO28);	break;
			case MBED_GPIO29:	pinNo = (1 << GPIO29);	break;
			case MBED_GPIO30:	pinNo = (1 << GPIO30);	break;
			default: return;
		}

		if (val == GP_LOW) {
			GPIO_ClearValue(portNo, pinNo);
		} else {
			GPIO_SetValue(portNo, pinNo);
		}
	}
}

uint8_t GPIOReadVal(uint32_t pin) {
	uint8_t portNo;
	uint32_t pinNo;

	if (_mbedGPICfg & pin) {
		if (MBED_GPIO_P0 & pin) {
			portNo = 0;
		} else if (MBED_GPIO_P1 & pin) {
			portNo = 1;
		} else if (MBED_GPIO_P2 & pin) {
			portNo = 2;
		} else {
			return GP_ERR;
		}

		switch (pin) {
			case MBED_GPIO5:	pinNo = (1 << GPIO5);	break;
			case MBED_GPIO6:	pinNo = (1 << GPIO6);	break;
			case MBED_GPIO7:	pinNo = (1 << GPIO7);	break;
			case MBED_GPIO8:	pinNo = (1 << GPIO8);	break;
			case MBED_GPIO9:	pinNo = (1 << GPIO9);	break;
			case MBED_GPIO10:	pinNo = (1 << GPIO10);	break;
			case MBED_GPIO11:	pinNo = (1 << GPIO11);	break;
			case MBED_GPIO12:	pinNo = (1 << GPIO12);	break;
			case MBED_GPIO13:	pinNo = (1 << GPIO13);	break;
			case MBED_GPIO14:	pinNo = (1 << GPIO14);	break;
			case MBED_GPIO15:	pinNo = (1 << GPIO15);	break;
			case MBED_GPIO16:	pinNo = (1 << GPIO16);	break;
			case MBED_GPIO17:	pinNo = (1 << GPIO17);	break;
			case MBED_GPIO18:	pinNo = (1 << GPIO18);	break;
			case MBED_GPIO19:	pinNo = (1 << GPIO19);	break;
			case MBED_GPIO20:	pinNo = (1 << GPIO20);	break;
			case MBED_GPIO21:	pinNo = (1 << GPIO21);	break;
			case MBED_GPIO22:	pinNo = (1 << GPIO22);	break;
			case MBED_GPIO23:	pinNo = (1 << GPIO23);	break;
			case MBED_GPIO24:	pinNo = (1 << GPIO24);	break;
			case MBED_GPIO25:	pinNo = (1 << GPIO25);	break;
			case MBED_GPIO26:	pinNo = (1 << GPIO26);	break;
			case MBED_GPIO27:	pinNo = (1 << GPIO27);	break;
			case MBED_GPIO28:	pinNo = (1 << GPIO28);	break;
			case MBED_GPIO29:	pinNo = (1 << GPIO29);	break;
			case MBED_GPIO30:	pinNo = (1 << GPIO30);	break;
			default: return GP_ERR;
		}

		if ( GPIO_ReadValue(portNo) & pinNo ) {
			return GP_HIGH;
		} else {
			return GP_LOW;
		}
	} else {
		return GP_ERR;
	}
}

