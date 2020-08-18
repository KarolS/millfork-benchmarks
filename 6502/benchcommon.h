#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

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

#if __VBCC__ 
static void cputs(const char *p) {
    while(*p) putchar(*p++);
}
static const unsigned int masks[] = {40000, 4000, 400, 40, 4};
static void utoa(unsigned int w, char* buffer, unsigned char radix) {
    char digits;
    char lastdigit;
    unsigned int mask;
    unsigned char i;
    digits = 0;
    for (i = 0; i < 5; ++i) {
        mask = masks[i];
        lastdigit = 0;
        while (w >= mask) {
            w -= mask;
            lastdigit += 4;
        }
        mask >>= 2;
        while (w >= mask) {
            w -= mask;
            lastdigit += 1;
        }
        if (digits != 0 || lastdigit != 0) {
            putchar('0' + lastdigit);
            ++digits;
        }
    }
    if (digits == 0) {
        putchar('0');
    }
}

#endif