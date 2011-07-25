#ifndef LED_H
#define LED_H

#include "LPC17xx.h"
#include "lpc17xx_gpio.h"

#define LEDS	0x00b40000
#define LED0	0x00040000
#define LED1	0x00100000
#define LED2	0x00200000
#define LED3	0x00800000

__INLINE static void initLED(void);
__INLINE static void turnOnLED(uint32_t);
__INLINE static void turnOffLED(uint32_t);

#endif

