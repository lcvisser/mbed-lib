#include <stdio.h>
#include <string.h>

#include "mbed.h"

void sizes(void) {
	/* Basic data type: char */
	miniUSBPrint("sizeof(char) = %u\r\n", sizeof(char));
	
	/* Basic data type: short int */
	miniUSBPrint("sizeof(short int) = %u\r\n", sizeof(short int));
	
	/* Basic data type: int */
	miniUSBPrint("sizeof(int) = %u\r\n", sizeof(int));
	
	/* Basic data type: long int */
	miniUSBPrint("sizeof(long int) = %u\r\n", sizeof(long int));
	
	/* Basic data type: long long int */
	miniUSBPrint("sizeof(long long int) = %u\r\n", sizeof(long long int));
	
	/* Basic data type: float */
	miniUSBPrint("sizeof(float) = %u\r\n", sizeof(float));
	
	/* Basic data type: double */
	miniUSBPrint("sizeof(double) = %u\r\n", sizeof(double));
	
	/* Basic data type: long double */
	miniUSBPrint("sizeof(long double) = %u\r\n", sizeof(long double));

	/* Data type: uint8_t */
	miniUSBPrint("sizeof(uint8_t) = %u\r\n", sizeof(uint8_t));
	
	/* Data type: uint16_t */
	miniUSBPrint("sizeof(uint16_t) = %u\r\n", sizeof(uint16_t));
	
	/* Data type: uint32_t */
	miniUSBPrint("sizeof(uint32_t) = %u\r\n", sizeof(uint32_t));

	/* Data type: uint64_t */
	miniUSBPrint("sizeof(uint64_t) = %u\r\n", sizeof(uint64_t));
}	

