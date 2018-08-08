#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#pragma static-locals(1);

static unsigned char toHex(unsigned char nibble) {
    unsigned char n = nibble & 0xf;
    if (n < 10) return n + '0';
    else return n + 'A' - 10;
}

static clock_t Ticks;

static void start(void) {
    Ticks = clock();
}
static void end(void) {
    Ticks = clock() - Ticks;
    putchar(toHex(Ticks>>20));
    putchar(toHex(Ticks>>16));
    putchar(toHex(Ticks>>12));
    putchar(toHex(Ticks>>8));
    putchar(toHex(Ticks>>4));
    putchar(toHex(Ticks>>0));
    putchar(13);
}