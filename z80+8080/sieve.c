#include <benchcommon.h>

#define COUNT 16384
#define SQRT_COUNT 128

unsigned char Sieve[COUNT];
void round(void) {
    register unsigned char* S;
    register unsigned       I;
    register unsigned       J;
    memset(Sieve, 0, COUNT);
    I = 2;
    while (I < SQRT_COUNT) {
        if (Sieve[I] == 0) {
            /* Prime number - mark multiples */
            J = I<<1;
            S = &Sieve[J];
            while (J < COUNT) {
                *S = 1;
                S += I;
                J += I;
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

