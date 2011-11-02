#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mbed.h"

void storage(void) {
	uint8_t bytes[8] = {0};
	int i = 3;
	float f = 3.1415925;
	double d = 3.1415926535897930;

	/* Integer data storage */
	memset(bytes, 0, 8);
	memcpy(bytes, &i, sizeof(i));
	miniUSBPrint("int(%i) is stored as: 0x%02hX%02hX%02hX%02hX%02hX%02hX%02hX%02hX\r\n",
			i, bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);

	/* Float data storage */
	memset(bytes, 0, 8);
	memcpy(bytes, &f, sizeof(f));
	miniUSBPrint("float(%0.7f) is stored as: 0x%02hX%02hX%02hX%02hX%02hX%02hX%02hX%02hX\r\n",
			f, bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);

	/* Double data storage */
	memset(bytes, 0, 8);
	memcpy(bytes, &d, sizeof(d));
	miniUSBPrint("double(%0.16f) is stored as: 0x%02hX%02hX%02hX%02hX%02hX%02hX%02hX%02hX\r\n",
			d, bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
}

