#include "benchcommon.h"

static unsigned short fib(unsigned char i) {
    if (i<2) return 1;
    return fib(i-1) + fib(i-2);
}

int main (void)
{
    unsigned int i;
    start();
    for(i=0;i<=24;++i) {
        putchar((char)(32 + fib(i)));
    }
    putchar(13);
    end();    
    return EXIT_SUCCESS;
}
