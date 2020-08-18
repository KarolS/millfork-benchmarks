#include "benchcommon.h"
#if !__VBCC__
#include <conio.h>
#endif
#include <stdlib.h>

const unsigned char* const rom = (const unsigned char*)0xe000;

static unsigned short sum(void) {
    register unsigned int s;
    register const unsigned char* p;
    s = 0;
    for (p = rom; p; ++p)
    {
         s += *p;
    };
    return s;
}




int main (void)
{
    static char buffer[20];
    unsigned int i;
    start();
    for(i=0;i<6;++i) {
        utoa(sum(), buffer, 10);
        cputs(buffer);
        putchar(13);
    }
    end();    
    return EXIT_SUCCESS;
}
