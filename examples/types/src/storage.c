#include <stdio.h>
#include <string.h>

#include "mbed.h"

#define BUFSIZE	256

void storage(void) {
	char txbuf[BUFSIZE + 1] = {'\0'};
	char bytes[8] = {0};
	int i = 3;
	float f = 3.1415925;
	double d = 3.1415926535897930;

	/* Integer data storage */
	memset(bytes, 0, 8);
	memcpy(bytes, &i, sizeof(i));
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "int(3) (0x3) is stored as: 0x%02hX %02hX %02hX %02hX %02hX %02hX %02hX %02hX\r\n",
			bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
	miniUSBSend((uint8_t *)txbuf, strlen(txbuf));

	/* Float data storage */
	memset(bytes, 0, 8);
	memcpy(bytes, &f, sizeof(f));
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "float(3.1415925) (0x40 49 0F DA) is stored as: 0x%02hX %02hX %02hX %02hX %02hX %02hX %02hX %02hX\r\n",
			bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
	miniUSBSend((uint8_t *)txbuf, strlen(txbuf));

	/* Double data storage */
	memset(bytes, 0, 8);
	memcpy(bytes, &d, sizeof(d));
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "double(3.1415926535897930) (0x40 09 21 FB 54 44 2D 18) is stored as: 0x%02hX %02hX %02hX %02hX %02hX %02hX %02hX %02hX\r\n",
			bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
	miniUSBSend((uint8_t *)txbuf, strlen(txbuf));
}

