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

