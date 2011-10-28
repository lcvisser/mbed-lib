#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mbed.h"

#define BUFSIZE	256

/* Main function */
int main(void) {
	char txbuf[BUFSIZE + 1] = {'\0'};

	float f = 3.1415925;	/* Source value */;
	double d = 0.0;		/* Target */

	uint8_t sign = 0;	/* Sign bit */
	uint32_t frac = 0;	/* Fraction: 23 bits for single-precision float */
	uint8_t fexp = 0;	/* Float exponent: 8 bits */
	uint16_t dexp = 0;	/* Double exponent: 11 bits */

	/* Intermediate storage of single-precision value */
	union {
		float fval;
		uint8_t fbytes[4];
	} fvar;

	/* Intermediate storage of double-precision value */
	union {
		double dval;
		uint8_t dbytes[8];
	} dvar;

	/* Initialize the system. */
	initSys(INIT_LED | INIT_MUSB | INIT_TIMER0);
	
	/* Initialize variables */
	memset(fvar.fbytes, 0, 4);
	memset(dvar.dbytes, 0, 8);

	/* Get individual bytes of float value */
	fvar.fval = f;
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "Single-precision floating point value is stored as: 0x%02hX%02hX%02hX%02hX\r\n",
			fvar.fbytes[0], fvar.fbytes[1], fvar.fbytes[2], fvar.fbytes[3]);
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));

	/* Obtain sign and fractiont */
	sign = fvar.fbytes[3] & 0x80;								/* Sign bit */
	frac = ((fvar.fbytes[2] & 0x7f) << 16) | (fvar.fbytes[1] << 8) | fvar.fbytes[0];	/* Fraction: 23 bits */

	/* Calculate exponent value */
	fexp = ((fvar.fbytes[3] & 0x7f) << 1) | ((fvar.fbytes[2] & 0x80) >> 7);			/* Exponent: 8 bits */
	if (fexp == 0) {
		/* Special case: zero */
		dexp = 0;
	} else if (fexp == 0xff) {
		/* Special case: infinity or NaN */
		dexp = 0x7ff;
	} else {
		/* Single-precision bias is 127, double-precision bias is 1023 */
		dexp = 1023 - (127 - fexp);
	}

	/* Build double precision floating point */
	dvar.dbytes[7] = sign | ((dexp & 0x7f0) >> 4);				/* Sign bit and bits 10-4 of exponent */
	dvar.dbytes[6] = ((dexp & 0xf) << 4) | ((frac & 0x780000) >> 19);	/* Bits 3-0 of exponent and bits 51-48 of fraction */
	dvar.dbytes[5] = (frac & 0x7f800) >> 11;				/* Bits 47-40 of fraction */
	dvar.dbytes[4] = (frac & 0x7f8) >> 3;					/* Bits 39-32 of fraction */
	dvar.dbytes[3] = (frac & 0x7) << 5;					/* Bits 31-29 of fraction */
	dvar.dbytes[2] = 0;							/* Remaining bytes are all zero */
	dvar.dbytes[1] = 0;
	dvar.dbytes[0] = 0;
	d = dvar.dval;

	/* Print results */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sign: 0x%x, fraction: 0x%x, exponent: 0x%x, result: %0.16f\r\n", (unsigned int)sign, (unsigned int)frac, (unsigned int)dexp, d);
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));

	/* Loop forever */
	while (1) {
		ledOn(LED0);
		delay(MBED_TIMER0, 100);
		ledOff(LED0);
		delay(MBED_TIMER0, 100);
	}

	return 0;
}

