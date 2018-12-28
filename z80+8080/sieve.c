#include <benchcommon.h>

#define COUNT 16384
#define SQRT_COUNT 128

unsigned char Sieve[COUNT];
void round(void) {
    register unsigned char* S;
    register unsigned char  I;
    memset(Sieve, 0, COUNT);
    I = 2;
    while (I < SQRT_COUNT) {
        if (Sieve[I] == 0) {
            /* Prime number - mark multiples */
            S = &Sieve[I<<1];
            while (S < Sieve + COUNT) {
                *S = 1;
                S += I;
            }
        }
        ++I;
    }
}
int main (void)
{
    start();
    round();
    round();
    round();
    end();
    while(1);
    return EXIT_SUCCESS;
}

