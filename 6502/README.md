# Millfork benchmarks on 6502

### Measurement methodology

The target platform is Commodore 64 emulated via the VICE x64 emulator, version 3.1.

The program measures the number of frames as counted by the internal time-of-day counter, read via the `RDTIM` routine at address $FFDE.

The program is not allowed to disable or modify interrupts.

The `benchcommon` library provides the necessary `start` and `end` functions. The program should call `start`, run the benchmark, call `end` and either enter an infinite loop or drop to BASIC prompt.

The result is displayed on the screen as a hexadecimal value. Results below have been converted to decimal.

### Compared implementations

These benchmarks compare the Millfork compiler with the most popular C compiler for 6502, CC65, and with another 6502-oriented language, Atalan:

|&nbsp;&nbsp;&nbsp;&nbsp; | symbol            | compiler | version  | command line                                          | comment |
|-------------------------|-------------------|----------|----------|-------------------------------------------------------|-|
|![](../images/404040.png)| asm               | Millfork | 0.3.4    | `millfork -t c64 -O1`                                 | assembly implementation |
|                         | mfk-0.3.4-O1      | Millfork | 0.3.4    | `millfork -t c64 -O1`                                 | minimal optimization level to not generate dumb code|
|![](../images/008000.png)| mfk-0.3.4-O4      | Millfork | 0.3.4    | `millfork -t c64 -O4 -fipo -finline`                  | recommended options for good code |
|                         | mfk-0.3.4-O4-ill  | Millfork | 0.3.4    | `millfork -t c64 -O4 -fipo -finline -fillegals`       | |
|![](../images/66e266.png)| mfk-0.3.4-O4-ss   | Millfork | 0.3.4    | `millfork -t c64 -O4 -fipo -finline -fsoftware-stack` | used only for the `fib` benchmark |
|![](../images/2200aa.png)| atalan-2011       | Atalan   | 20110319 | `atalan -o 9`                                         | |
|                         | cc65-2.16-unopt   | CC65     | 2.16     | `cl65 -t c64`                                         | no optimizations |
|![](../images/aa0000.png)| cc65-2.16-opt     | CC65     | 2.16     | `cl65 -t c64 -r -Oirs`                                | recommended options for good code |

Remarks:

* `millfork` is a script launching the Millfork compiler with the correct `-I` option.

* Input and output file options have been omitted for brevity.

* I haven't been able to make Atalan compile benchmarks other than `sieve` without crashing.

* Charts show the most optimized results.

### Benchmark `sieve`

Source: [`sieve.c`](./sieve.c), [`sieve.mfk`](./sieve.mfk), [`sieve-asm.mfk`](./sieve-asm.mfk), [`sieveatl.atl`](./sieveatl.atl)

The benchmark calculates all the prime numbers from 1 to 2^(14) using the Sieve of Erasthotenes algorithm. It does it ten times, for more precise results.

Results:

|                         | symbol            | frames (less is better) |
|-|-|-:|
|![](../images/404040.png)| asm               | 700 |
|                         | mfk-0.3.4-O1      | 763 |
|![](../images/008000.png)| mfk-0.3.4-O4      | 701 |
|                         | mfk-0.3.4-O4-ill  | 702 |
|                         | mfk-0.3.4-O4-ss   | – |
|![](../images/2200aa.png)| atalan-2011       | 1375 |
|                         | cc65-2.16-unopt   | 6331 |
|![](../images/aa0000.png)| cc65-2.16-opt     | 920 |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:700|701|920|1375&chdl=asm|mfk-0.3.4-O4|cc65-2.16-opt|atalan-2011&chtt=Sieve%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=x,y&chco=404040,008000,aa0000,2200aa&chxl=0:||&chds=0,1500&chxr=1,0,1500)

### Benchmark `plasma`

Source: [`plasma.c`](./plasma.c), [`plasma.mfk`](./plasma.mfk)

The benchmark displays a plasma demo effect. 1000 frames are rendered.

The code is based on an example from the CC65 repository: https://github.com/cc65/cc65/blob/master/samples/plasma.c

Results:

|                         | symbol            | frames (less is better) |
|-|-|-:|
|![](../images/404040.png)| asm               | 1754 |
|                         | mfk-0.3.4-O1      | 1965 |
|![](../images/008000.png)| mfk-0.3.4-O4      | 1780 |
|                         | mfk-0.3.4-O4-ill  | 1764 |
|                         | mfk-0.3.4-O4-ss   | – |
|                         | atalan-2011       | n/a |
|                         | cc65-2.16-unopt   | 30112 |
|![](../images/aa0000.png)| cc65-2.16-opt     | 4003 |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:1754|1780|4003&chdl=asm|mfk-0.3.4-O4|cc65-2.16-opt&chtt=Plasma%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=x,y&chco=404040,008000,aa0000&chxl=0:||&chds=0,50000&chxr=1,0,5000)


### Benchmark `fib`

Source: [`fib.c`](./fib.c), [`fib.mfk`](./fib.mfk), [`fib-asm.mfk`](./fib-asm.mfk)

The benchmark calculates the first 25 Fibonacci numbers using the naïve recursive algorithm.

Results:

|                         | symbol            | frames (less is better) |
|-|-|-:|
|![](../images/404040.png)| asm               | 1309 |
|                         | mfk-0.3.4-O1      | 2156 |
|![](../images/008000.png)| mfk-0.3.4-O4      | 1476 |
|                         | mfk-0.3.4-O4-ill  | 1476 |
|![](../images/66e266.png)| mfk-0.3.4-O4-ss   | 1784 |
|                         | atalan-2011       | n/a |
|                         | cc65-2.16-unopt   | 4647 |
|![](../images/aa0000.png)| cc65-2.16-opt     | 3261 |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:1309|1476|1784|3261&chdl=asm|mfk-0.3.4-O4|mfk-0.3.4-O4-ss|cc65-2.16-opt&chtt=Fibonacci%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=x,y&chco=404040,008000,66e266,aa0000&chxl=0:||&chds=0,4000&chxr=1,0,4000)


### Benchmark `linkedlist`

Source: [`linkedlist.c`](./linkedlist.c), [`linkedlist.mfk`](./linkedlist.mfk)

The benchmark creates a single-linked list with 3000 entries, with a 16-bit integer at each node, and then traverses the list and sums all the values together. It does it five times, for more precise results.
 

Results:

|                         | symbol            | frames (less is better) |
|-|-|-:|
|                         | asm               | n/a |
|                         | mfk-0.3.4-O1      | 237 |
|![](../images/008000.png)| mfk-0.3.4-O4      | 219 |
|                         | mfk-0.3.4-O4-ill  | 215 |
|                         | mfk-0.3.4-O4-ss   | 219 |
|                         | atalan-2011       | n/a |
|                         | cc65-2.16-unopt   | 1401 |
|![](../images/aa0000.png)| cc65-2.16-opt     | 414 |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:219|414&chdl=mfk-0.3.4-O4|cc65-2.16-opt&chtt=Linked%20list%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=x,y&chco=008000,aa0000&chxl=0:||&chds=0,500&chxr=1,0,500)

