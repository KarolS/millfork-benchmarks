#include "benchcommon.h"

static unsigned short __fastcall(fib(unsigned char i)) {
    if (i<2) return 1;
    return fib(i-1) + fib(i-2);
}

int main (void)
{
    unsigned int i;
    start();
    for(i=0;i<=24;++i) {
        putchar((char)(fib(i) & 0x7f | 0x20));
    }
    putchar(13);
    end();    
    return EXIT_SUCCESS;
}
