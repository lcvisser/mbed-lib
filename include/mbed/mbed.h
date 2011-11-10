/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

/*!
 * \file
 *
 * In this file are all necessary defines for the mbed platform. Also, all
 * all header files are included here for convience, so that including this
 * header file is sufficient.
 */

#include "LPC17xx.h"
#include "mbed_can.h"
#include "mbed_gpio.h"
#include "mbed_led.h"
#include "mbed_musb.h"
#include "mbed_serial.h"
#include "mbed_timer.h"

#ifndef MBED_H
#define MBED_H	/*!< Header guard. */

/*! \defgroup initflags Initalization flags
 * These flags indicate which functionality should be initialized.
 * \sa initSys()
 * @{
 */
#define INIT_LED	(1 << 1)	/*!< Initialize the four blue LEDs. */
#define INIT_MUSB	(1 << 2)	/*!< Serial on mini USB-B port (UART0). */
#define INIT_SERIAL0	(1 << 3)	/*!< Serial on DIP 13/14 (UART1). */
#define INIT_SERIAL1	(1 << 4)	/*!< Serial on DIP 27/28 (UART2). */
#define INIT_SERIAL2	(1 << 5)	/*!< Serial on DIP 9/10 (UART3). */
#define INIT_CAN0	(1 << 6)	/*!< CAN on DIP 9/10 (CAN1). */
#define INIT_CAN1	(1 << 7)	/*!< CAN on DIP 29/30 (CAN2). */
#define INIT_TIMER0	(1 << 8)	/*!< Initialize TIMER0. */
#define INIT_TIMER1	(1 << 9)	/*!< Initialize TIMER1. */
#define INIT_TIMER2	(1 << 10)	/*!< Initialize TIMER2. */
#define INIT_TIMER3	(1 << 11)	/*!< Initialize TIMER3. */
#define INIT_GPI	(1 << 12)	/*!< Initialize general purpose input ports. */
#define INIT_GPO	(1 << 13)	/*!< Initialize general purpose output ports. */
/*! @} */

/*! \defgroup statusflags Status flags
 * These flags indicate which functionality has been successfully initialized.
 * @{
 */
#define MBED_SYS_INIT		(1 << 0)	/*!< System initialization complete. */
#define MBED_LED_INIT		(1 << 1)	/*!< The four LEDs are initialized. */
#define MBED_MUSB_INIT		(1 << 2)	/*!< Serial communication functionality on the mini USB-B port initialized. */
#define MBED_SERIAL0_INIT	(1 << 3)	/*!< UART1 initialized. */
#define MBED_SERIAL1_INIT	(1 << 4)	/*!< UART2 initialized. */
#define MBED_SERIAL2_INIT	(1 << 5)	/*!< UART3 initialized. */
#define MBED_CAN0_INIT		(1 << 6)	/*!< CAN1 initialized. */
#define MBED_CAN1_INIT		(1 << 7)	/*!< CAN2 initialized. */
#define MBED_TIMER0_INIT	(1 << 8)	/*!< TIMER0 initialized. */
#define MBED_TIMER1_INIT	(1 << 9)	/*!< TIMER1 initialized. */
#define MBED_TIMER2_INIT	(1 << 10)	/*!< TIMER2 initialized. */
#define MBED_TIMER3_INIT	(1 << 11)	/*!< TIMER3 initialized. */
#define MBED_GPI_INIT		(1 << 12)	/*!< General purpose inputs initialized. */
#define MBED_GPO_INIT		(1 << 13)	/*!< General purpose outputs initialized. */
/*! @} */

/*! \defgroup gpio General purpose I/O pins
 * Enumeration of general purpose I/O pins.
 * @{
 */
#define MBED_GPIOX	(1 << 0)	/*!< Not configured. */
#define MBED_GPIO5	(1 << 1)	/*!< DIP 5. */
#define MBED_GPIO6	(1 << 2)	/*!< DIP 6. */
#define MBED_GPIO7	(1 << 3)	/*!< DIP 7. */
#define MBED_GPIO8	(1 << 4)	/*!< DIP 8. */
#define MBED_GPIO9	(1 << 5)	/*!< DIP 9. */
#define MBED_GPIO10	(1 << 6)	/*!< DIP 10. */
#define MBED_GPIO11	(1 << 7)	/*!< DIP 11. */
#define MBED_GPIO12	(1 << 8)	/*!< DIP 12. */
#define MBED_GPIO13	(1 << 9)	/*!< DIP 13. */
#define MBED_GPIO14	(1 << 10)	/*!< DIP 14. */
#define MBED_GPIO15	(1 << 11)	/*!< DIP 15. */
#define MBED_GPIO16	(1 << 12)	/*!< DIP 16. */
#define MBED_GPIO17	(1 << 13)	/*!< DIP 17. */
#define MBED_GPIO18	(1 << 14)	/*!< DIP 18. */
#define MBED_GPIO19	(1 << 15)	/*!< DIP 19. */
#define MBED_GPIO20	(1 << 16)	/*!< DIP 20. */
#define MBED_GPIO21	(1 << 17)	/*!< DIP 21. */
#define MBED_GPIO22	(1 << 18)	/*!< DIP 22. */
#define MBED_GPIO23	(1 << 19)	/*!< DIP 23. */
#define MBED_GPIO24	(1 << 20)	/*!< DIP 24. */
#define MBED_GPIO25	(1 << 21)	/*!< DIP 25. */
#define MBED_GPIO26	(1 << 22)	/*!< DIP 26. */
#define MBED_GPIO27	(1 << 23)	/*!< DIP 27. */
#define MBED_GPIO28	(1 << 24)	/*!< DIP 28. */
#define MBED_GPIO29	(1 << 25)	/*!< DIP 29. */
#define MBED_GPIO30	(1 << 26)	/*!< DIP 30. */
/*! @} */

/*! \defgroup ports Port configuration
 * Configuration of GPIO pins on the different ports.
 * @{
 */
#define MBED_GPIO_P0	(MBED_GPIO5 | MBED_GPIO6 | MBED_GPIO7 | MBED_GPIO8 | MBED_GPIO9 | MBED_GPIO10 | MBED_GPIO11 | MBED_GPIO12 | MBED_GPIO13 | MBED_GPIO14 | MBED_GPIO15 | MBED_GPIO16 | MBED_GPIO17 | MBED_GPIO18 | MBED_GPIO27 | MBED_GPIO28 | MBED_GPIO29 | MBED_GPIO30)			/*!< GPIO on port 0. */
#define MBED_GPIO_P1	(MBED_GPIO19 | MBED_GPIO20)								/*!< GPIO on port 1. */
#define MBED_GPIO_P2	(MBED_GPIO21 | MBED_GPIO22 | MBED_GPIO23 | MBED_GPIO24 | MBED_GPIO25 | MBED_GPIO26)	/*!< GPIO on port 2. */
/*! @} */

/*! \defgroup deviceid Device IDs
 * ID enumeration of various devices.
 * @{
 */
#define MBED_SERIAL0	0		/*!< UART1 on DIP 13/14. */
#define MBED_SERIAL1	1		/*!< UART2 on DIP 27/28. */
#define MBED_SERIAL2	2		/*!< UART3 on DIP 9/10. */
#define MBED_CAN0	0		/*!< CAN1 on DIP 9/10. */
#define MBED_CAN1	1		/*!< CAN2 on DIP 29/30. */
#define MBED_TIMER0	0		/*!< TIMER0. */
#define MBED_TIMER1	1		/*!< TIMER1. */
#define MBED_TIMER2	2		/*!< TIMER2. */
#define MBED_TIMER3	3		/*!< TIMER3. */
/*! @} */

/*! Global status register. */
uint32_t mbedStatus;

/* Function definitions. */
void initSys(uint32_t);

#endif

