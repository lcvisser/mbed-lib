#include <string.h>

#include "LPC17xx.h"
#include "lpc17xx_gpio.h"

/* Counter for milliseconds */
volatile uint32_t msTicks;

/* Handler for SysTick interrupt */
void SysTick_Handler(void) {
	msTicks++;
}

/* Main initialization function */
__INLINE static void sysInit(void) {
	/* Update system clock register and reset counter. */
	SystemCoreClockUpdate();
	msTicks = 0;

	/* Try to initialize the SysTick counter for 1ms interrupt. */
	if (SysTick_Config(SystemCoreClock/1000)) {
		/* Infinite loop on error. */
		while (1) ;
	}
}

/* Wait function */
__INLINE static void wait(uint32_t msecs) {
	uint32_t currTickCount = msTicks;

	/* Loop until desired delay is achieved. */
	while ((msTicks - currTickCount) < msecs) ;
}

