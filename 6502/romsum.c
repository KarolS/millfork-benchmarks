#include "benchcommon.h"
#include <conio.h>
#include <stdlib.h>

const unsigned char* const rom = (const unsigned char*)0xe000;

static unsigned short sum(void) {
    unsigned int s;
    const unsigned char* p;
    unsigned char page;
    unsigned char i;
    p = rom;
    s = 0;
    /* doing it page-by-page is faster than doing just one huge loop */
    for (page = 0; page < 0x20; page++) {
        i = 0;
        do {
            s += p[i];
            i++;
        } while (i);
        /* this is faster than p += 0x100; */
        *((unsigned char*)&p + 1) += 1;
    }
    return s;
}




int main (void)
{
    static char buffer[20];
    unsigned int i;
    start();
    for(i=0;i<6;i++) {
        utoa(sum(), buffer, 10);
        cputs(buffer);
        putchar(13);
    }
    end();    
    return EXIT_SUCCESS;
}
