%import textio

main {

    const uword COUNT = 16384
    const uword SQRT_COUNT = 128
    const uword Sieve = $4000

    sub sieve_round() {
        uword S
        ubyte I = 2
        memset(Sieve, COUNT, 0)
        ; txt.print("primes: ")
        while I < SQRT_COUNT {
            if @(Sieve + I) == 0 {
                ; txt.print_ub(I)
                ; txt.chrout(' ')
                S = Sieve + (I << 1)
                while S < Sieve + COUNT {
                    @(S) = 1
                    S += I
                }
            }
            I ++
        }
        ; txt.chrout('\n')
    }

    sub start() {
        benchcommon.begin()

        sieve_round()
        sieve_round()
        sieve_round()
        sieve_round()
        sieve_round()

        sieve_round()
        sieve_round()
        sieve_round()
        sieve_round()
        sieve_round()

        benchcommon.end()
    }
}



benchcommon {
    uword last_time = 0
    uword time_start = 0


    asmsub read_time () clobbers(A,X,Y) {
        %asm {{
            jsr $FFDE
            sta last_time
            stx last_time+1
            rts
        }}
    }

    sub begin() {
        benchcommon.read_time()
        benchcommon.time_start = benchcommon.last_time
    }

    sub end() {
        benchcommon.read_time()

        txt.print_uwhex(benchcommon.last_time-benchcommon.time_start, false)
        txt.chrout('\n')

        void txt.input_chars($c000)
    }
}

