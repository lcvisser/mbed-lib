/* Copyright (c) Ludo Visser
 *
 * This file is part of the mbed-lib project, and is distributed under the
 * terms of the MIT License. The full license agreement text can be found
 * in the LICENSE file.
 */

#include <sys/types.h>

extern int __cs3_heap_start;

caddr_t _sbrk(int increment) {
	static unsigned char* heap = NULL;
	unsigned char* prev_heap = NULL;

	/* Initialize heap pointer */
	if (heap == NULL) {
		heap = (unsigned char*)(&__cs3_heap_start);
	}

	prev_heap = heap;
	heap += increment;

	return (caddr_t)prev_heap;
}

