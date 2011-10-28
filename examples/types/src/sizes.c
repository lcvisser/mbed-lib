#include <stdio.h>
#include <string.h>

#include "mbed.h"

#define BUFSIZE	256

void sizes(void) {
	char txbuf[BUFSIZE + 1] = {'\0'};
	
	/* Basic data type: char */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(char) = %u\r\n", sizeof(char));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));
	
	/* Basic data type: short int */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(short int) = %u\r\n", sizeof(short int));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));
	
	/* Basic data type: int */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(int) = %u\r\n", sizeof(int));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));
	
	/* Basic data type: long int */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(long int) = %u\r\n", sizeof(long int));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));
	
	/* Basic data type: long long int */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(long long int) = %u\r\n", sizeof(long long int));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));
	
	/* Basic data type: float */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(float) = %u\r\n", sizeof(float));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));
	
	/* Basic data type: double */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(double) = %u\r\n", sizeof(double));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));
	
	/* Basic data type: long double */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(long double) = %u\r\n", sizeof(long double));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));

	/* Data type: uint8_t */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(uint8_t) = %u\r\n", sizeof(uint8_t));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));
	
	/* Data type: uint16_t */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(uint16_t) = %u\r\n", sizeof(uint16_t));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));
	
	/* Data type: uint32_t */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(uint32_t) = %u\r\n", sizeof(uint32_t));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));

	/* Data type: uint64_t */
	memset(txbuf, '\0', BUFSIZE);
	snprintf(txbuf, BUFSIZE, "sizeof(uint64_t) = %u\r\n", sizeof(uint64_t));
	miniUSBSend((uint8_t*)txbuf, strlen(txbuf));
}	

