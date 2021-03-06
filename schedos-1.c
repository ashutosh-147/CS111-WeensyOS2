#include "schedos-app.h"
#include "x86sync.h"

/*****************************************************************************
 * schedos-1
 *
 *   This tiny application prints red "1"s to the console.
 *   It yields the CPU to the kernel after each "1" using the sys_yield()
 *   system call.  This lets the kernel (schedos-kern.c) pick another
 *   application to run, if it wants.
 *
 *   The other schedos-* processes simply #include this file after defining
 *   PRINTCHAR appropriately.
 *
 *****************************************************************************/

#ifndef PRINTCHAR
#define PRINTCHAR	('1' | 0x0C00)
#endif

void
start(void)
{
	int i;
    if(PRINTCHAR == ('1' | 0x0C00))
        sys_set_priority(1);
    else if(PRINTCHAR == ('2' | 0x0A00))
        sys_set_priority(1);
    else if(PRINTCHAR == ('3' | 0x0900))
        sys_set_priority(3);
    else if(PRINTCHAR == ('4' | 0x0E00))
        sys_set_priority(2);

	for (i = 0; i < RUNCOUNT; i++) {
		// Write characters to the console, yielding after each one.
		//*cursorpos++ = PRINTCHAR;
        sys_print(PRINTCHAR);
		sys_yield();
	}

	// Yield forever.
	//while (1)
	//	sys_yield();

    sys_exit(0);
}
