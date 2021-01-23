%import textio

main {

    const uword rom = $e000

    sub sumrom() -> uword {
        uword p = rom
        uword s = 0
        repeat $100-$e0 {
            ubyte ix
            for ix in 0 to 255 {
                s += @(p+ix)
            }
            p += $100
        }
        return s
    }

    sub start() {
        benchcommon.begin()
        ubyte i
        for i in 0 to 5 {
            txt.print_uw(sumrom())
            txt.chrout('\n')
        }
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

