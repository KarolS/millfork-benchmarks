%import textio

; note: requires at least Prog8 6.1 to compile

main {
    uword  free
    uword  root
    uword  heap

    sub start() {
        heap = memory("heap", 4000*4)

        benchcommon.begin()
        repeat 5 {
            init()
            uword i
            for i in 0 to 2999
                prepend(i)

            txt.chrout(lsb(calc_sum()))
        }
        txt.nl()
        benchcommon.end()
    }

    sub init() {
        free = 0
        root = 0
    }

    sub alloc() -> uword {
        uword result = free
        result *= 4
        result += heap
        free++
        return result
    }

    sub prepend(uword x) {
        uword new = alloc()

        ; prog8 doesn't yet support typed pointers and corresponding pointer dereferencing
        ; so instead we write directly into the memory locations
        pokew(new, root)
        pokew(new+2, x)
        root = new
    }

    sub calc_sum() -> uword {
        uword current = root
        uword s = 0
        while current {
            ; prog8 doesn't yet support typed pointers and corresponding pointer dereferencing
            ; so instead we read directly from the memory locations
            s += peekw(current+2)
            current = peekw(current)
        }
        return s
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
