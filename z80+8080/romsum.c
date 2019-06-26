#include "benchcommon.h"
#include <stdlib.h>

const unsigned char* const rom = ((const unsigned char*)0);

static unsigned short sum(void) {
    unsigned int s;
    const unsigned char* p;
    unsigned int i;
    p = rom;
    s = 0;
    for (i = 0; i < 0x4000; i++) {
            s += p[i];
    }
    return s;
}




int main (void)
{
    static char buffer[20];
    unsigned int i;
    start();
    for(i=0;i<20;i++) {
        utoa(sum(), buffer, 10);
        puts(buffer);
        putchar(13);
    }
    end();    
    return EXIT_SUCCESS;
}
