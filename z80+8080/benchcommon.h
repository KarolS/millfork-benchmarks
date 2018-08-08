#ifdef __SDCC
	#ifndef SDCC
	#define SDCC
	#endif
#endif

#ifdef __SCCZ80
	#ifndef SCCZ80
	#define SCCZ80
	#endif
#endif

#ifdef SDCC
	__at (0x5c78) long frames;
	#define __fastcall(fn)    fn __z88dk_fastcall
	#define OK
	
	static inline void di(void) {
		__asm__("di");
	}
	static inline void ei(void) {
		__asm__("ei");
	}
#endif

#ifdef SCCZ80
	extern long frames @0x5c78;
	#define __fastcall(fn)    __FASTCALL__ fn
	#define __critical(fn)    __critical fn
	#define OK
	
	static void di(void) {
		#asm
		di
		#endasm
	}
	static void ei(void) {
		#asm
		ei
		#endasm
	}
#endif

#ifndef OK 
#error Only SDCC and SCCZ80 are supported
#endif

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


static unsigned char toHex(unsigned char nibble) {
    unsigned char n = nibble & 0xf;
    if (n < 10) return n + '0';
    else return n + 'A' - 10;
}

static long Ticks;
static long Start;

static void snapshot(void){
	di();
    Ticks = frames & 0xffffff;
	ei();
}
static void start(void) {
	snapshot();
	Start = Ticks;
}
static void printTicks(void) {
    putchar(toHex(Ticks>>20));
    putchar(toHex(Ticks>>16));
    putchar(toHex(Ticks>>12));
    putchar(toHex(Ticks>>8));
    putchar(toHex(Ticks>>4));
    putchar(toHex(Ticks>>0));
    putchar(13);
}
static void end(void) {
	snapshot();
    Ticks -= Start;
    printTicks();
}