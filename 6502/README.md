# Millfork benchmarks on 6502

### Measurement methodology

The target platform is Commodore 64 emulated via the VICE x64 emulator, version 3.1.

The program measures the number of frames as counted by the internal time-of-day counter, read via the `RDTIM` routine at address $FFDE.

The program is not allowed to disable or modify interrupts.

The `benchcommon` library provides the necessary `start` and `end` functions. The program should call `start`, run the benchmark, call `end` and either enter an infinite loop or drop to BASIC prompt.

The result is displayed on the screen as a hexadecimal value. Results below have been converted to decimal.

### Compared implementations

# Warning: These benchmark are not actually against Millfork 0.3.2, but against the current development version.

These benchmarks compare the Millfork compiler with the most popular C compiler for 6502, CC65, and with another 6502-oriented language, Atalan:

| symbol            | compiler | version  | command line                                          | comment |
|-------------------|----------|----------|-------------------------------------------------------|-|
| asm               | Millfork | 0.3.2    | `millfork -t c64 -O1`                                 | assembly implementation |
| mfk-0.3.2-O1      | Millfork | 0.3.2    | `millfork -t c64 -O1`                                 | minimal optimization level to not generate dumb code|
| mfk-0.3.2-O4      | Millfork | 0.3.2    | `millfork -t c64 -O4 -fipo -finline`                  | recommended options for good code |
| mfk-0.3.2-O4-ill  | Millfork | 0.3.2    | `millfork -t c64 -O4 -fipo -finline -fillegals`       | |
| mfk-0.3.2-O4-ss   | Millfork | 0.3.2    | `millfork -t c64 -O4 -fipo -finline -fsoftware-stack` | used only for the `fib` benchmark |
| atalan-2011       | Atalan   | 20110319 | `atalan -o 9`                                         | |
| cc65-2.16-unopt   | CC65     | 2.16     | `cl65 -t c64`                                         | no optimizations |
| cc65-2.16-opt     | CC65     | 2.16     | `cl65 -t c64 -r -Oirs`                                | recommended options for good code |

Remarks:

* `millfork` is a script launching the Millfork compiler with the correct `-I` option.

* Input and output file options have been omitted for brevity.

* I haven't been able to make Atalan compile benchmarks other than `sieve` without crashing.

* Charts show the most optimized results.

### Benchmark `sieve`

Source: [`sieve.c`](./sieve.c), [`sieve.mfk`](./sieve.mfk), [`sieveatl.atl`](./sieveatl.atl)

The benchmark calculates all the prime numbers from 1 to 2^(14) using the Sieve of Erasthotenes algorithm. It does it ten times, for more precise results.

Results:

| symbol            | frames (less is better) |
|-|-:|
| asm               | 701 |
| mfk-0.3.2-O1      | 763 |
| mfk-0.3.2-O4      | 701 |
| mfk-0.3.2-O4-ill  | 702 |
| mfk-0.3.2-O4-ss   | – |
| atalan-2011       | 1490 |
| cc65-2.16-unopt   | 6331 |
| cc65-2.16-opt     | 920 |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:701|701|920|1490&chdl=asm|mfk-0.3.2-O4|cc65-2.16-opt|atalan-2011&chtt=Sieve%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=x,y&chco=404040,008000,aa0000,2200aa&chxl=0:||&chds=0,1500&chxr=1,0,1500)

### Benchmark `plasma`

Source: [`plasma.c`](./plasma.c), [`plasma.mfk`](./plasma.mfk)

The benchmark displays a plasma demo effect. 1000 frames are rendered.

The code is based on an example from the CC65 repository: https://github.com/cc65/cc65/blob/master/samples/plasma.c

Results:

| symbol            | frames (less is better) |
|-|-:|
| asm               | – |
| mfk-0.3.2-O1      | 3459 |
| mfk-0.3.2-O4      | 3458 |
| mfk-0.3.2-O4-ill  | 3458 |
| mfk-0.3.2-O4-ss   | – |
| atalan-2011       | n/a |
| cc65-2.16-unopt   | 30112 |
| cc65-2.16-opt     | 4003 |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:1111|3458|4003&chdl=asm|mfk-0.3.2-O4|cc65-2.16-opt&chtt=Plasma%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=x,y&chco=404040,008000,aa0000&chxl=0:||&chds=0,50000&chxr=1,0,5000)


### Benchmark `fib`

Source: [`fib.c`](./fib.c), [`fib.mfk`](./fib.mfk)

The benchmark calculates the first 25 Fibonacci numbers using the naïve recursive algorithm.

Results:

| symbol            | frames (less is better) |
|-|-:|
| asm               | 1309 |
| mfk-0.3.2-O1      | 2156 |
| mfk-0.3.2-O4      | 1476 |
| mfk-0.3.2-O4-ill  | 1476 |
| mfk-0.3.2-O4-ss   | 1784 |
| atalan-2011       | n/a |
| cc65-2.16-unopt   | 4647 |
| cc65-2.16-opt     | 3261 |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:1309|1476|1784|3261&chdl=asm|mfk-0.3.2-O4|mfk-0.3.2-O4-ss|cc65-2.16-opt&chtt=Fibonacci%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=x,y&chco=404040,008000,66e266,aa0000&chxl=0:||&chds=0,4000&chxr=1,0,4000)

