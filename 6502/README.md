# Millfork benchmarks on 6502

### Measurement methodology

The target platform is Commodore 64 emulated via the VICE x64 emulator, version 3.1.

The program measures the number of frames as counted by the internal time-of-day counter, read via the `RDTIM` routine at address $FFDE.

The program is not allowed to disable or modify interrupts.

The `benchcommon` library provides the necessary `start` and `end` functions. The program should call `start`, run the benchmark, call `end` and either enter an infinite loop or drop to BASIC prompt.

The result is displayed on the screen as a hexadecimal value. Results below have been converted to decimal.

### Compared implementations

These benchmarks compare the Millfork compiler with the most popular C compiler for 6502, CC65, and with other 6502-oriented languages: Atalan, Prog8 and KickC:

|&nbsp;&nbsp;&nbsp;&nbsp; | symbol            | compiler | version  | command line                                          | comment |
|-------------------------|-------------------|----------|----------|-------------------------------------------------------|-|
|![](../images/404040.png)| asm               | Millfork | 0.3.18   | `millfork -t c64 -O1`                                 | assembly implementation |
|                         | mfk-0.3.18-O1     | Millfork | 0.3.18   | `millfork -t c64 -O1`                                 | minimal optimization level to not generate dumb code|
|![](../images/008000.png)| mfk-0.3.18-O4     | Millfork | 0.3.18   | `millfork -t c64 -O4 -fipo -finline`                  | recommended options for good code |
|                         | mfk-0.3.18-O4-ill | Millfork | 0.3.18   | `millfork -t c64 -O4 -fipo -finline -fillegals`       | |
|![](../images/66e266.png)| mfk-0.3.18-O4-ss  | Millfork | 0.3.18   | `millfork -t c64 -O4 -fipo -finline -fsoftware-stack` | used only for the `fib` benchmark |
|![](../images/2200aa.png)| atalan-2011       | Atalan   | 20110319 | `atalan -o 9`                                         | |
|                         | cc65-2.16-unopt   | CC65     | 2.16     | `cl65 -t c64`                                         | no optimizations |
|![](../images/aa0000.png)| cc65-2.16-opt     | CC65     | 2.16     | `cl65 -t c64 -r -Oirs`                                | recommended options for good code |
|                         | cc65-2.18-unopt   | CC65     | 2.18     | `cl65 -t c64`                                         | no optimizations |
|                         | cc65-2.18-opt     | CC65     | 2.18     | `cl65 -t c64 -r -Oirs`                                | recommended options for good code |
|                         | vbcc-0.9h-unopt   | VBCC     | 0.9h     | `vc`                                                  | no optimizations |
|![](../images/96c1ee.png)| vbcc-0.9h-opt     | VBCC     | 0.9h     | `vc -O3`                                              | recommended options for good code |
|                         | prog8-3.2         | Prog8    | 3.2      |                                                       | |
|![](../images/ff7f27.png)| kickc-0.8.2       | KickC    | 0.8.2    |                                                       | | 
|                         | basic-boss        | BASIC-BOSS | 2.40   |                                                       | |

Remarks:

* Input and output file options have been omitted for brevity.

* I haven't been able to make Atalan compile benchmarks other than `sieve` and `romsum` without crashing.

* Language limitations make it very hard, if not impossible, to implement `fib` in KickC and `fib` and `linkedlist` in Prog8.

* BASIC-BOSS was included as a curiosity, to compare the 1988 technology with more modern solutions. Due to various limitations, only the `sieve` benchmark was implemented and it displays the timing in decimal, not hexadecimal.

* CC65 2.18 is not faster at these benchmarks than CC65 2.16.

* Pas6502 was considered. It will be included in the benchmarks when it gets more mature.

* Charts show the most optimized results.

### Benchmark `sieve`

Source: [`sieve.c`](./sieve.c), [`sieve.mfk`](./sieve.mfk), [`sieve-asm.mfk`](./sieve-asm.mfk), [`sieveatl.atl`](./sieveatl.atl), [`sieve-p8.p8`](./sieve-p8.p8), [`sieve-kc.kc`](./sieve-kc.kc)

The benchmark calculates all the prime numbers from 1 to 2^(14) using the Sieve of Erasthotenes algorithm. It does it ten times, for more precise results.

Results:

|                         | symbol            | frames (less is better) |
|-|-|-:|
|![](../images/404040.png)| asm               | 701 |
|                         | mfk-0.3.18-O1     | 762 |
|![](../images/008000.png)| mfk-0.3.18-O4     | 701 |
|                         | mfk-0.3.18-O4-ill | 701 |
|                         | mfk-0.3.18-O4-ss  | – |
|![](../images/2200aa.png)| atalan-2011       | 1375 |
|                         | cc65-2.16-unopt   | 6331 |
|![](../images/aa0000.png)| cc65-2.16-opt     | 919 |
|                         | cc65-2.18-unopt   | 6331 |
|                         | cc65-2.18-opt     | 919 |
|                         | vbcc-0.9h-unopt   | 992 |
|![](../images/96c1ee.png)| vbcc-0.9h-opt     | 992 |
|                         | prog8-3.2         | 2389 |
|![](../images/ff7f27.png)| kickc-0.8.2       | 992 |
|                         | basic-boss        | 2406 |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:701|701|919|992|992|1375&chdl=asm|mfk-0.3.18-O4|cc65-2.16-opt|vbcc-0.9h-opt|kickc-0.8.2|atalan-2011&chtt=Sieve%20benchmark%20%28time%20in%20frames,%20less%20is%20better%29&chma=10,10&chxt=y,x&chco=404040,008000,aa0000,96c1ee,ff7f27,2200aa&chxl=0:||&chds=0,1500&chxr=1,0,1500)

### Benchmark `plasma`

Source: [`plasma.c`](./plasma.c), [`plasma.mfk`](./plasma.mfk), [`plasma-kc.kc`](./plasma-kc.kc)

The benchmark displays a plasma demo effect. 1000 frames are rendered.

The code is based on an example from the CC65 repository: https://github.com/cc65/cc65/blob/master/samples/plasma.c

Results:

|                         | symbol            | frames (less is better) |
|-|-|-:|
|![](../images/404040.png)| asm               | 1754 |
|                         | mfk-0.3.18-O1     | 1920 |
|![](../images/008000.png)| mfk-0.3.18-O4     | 1780 |
|                         | mfk-0.3.18-O4-ill | 1764 |
|                         | mfk-0.3.18-O4-ss  | – |
|                         | atalan-2011       | n/a |
|                         | cc65-2.16-unopt   | 30112 |
|![](../images/aa0000.png)| cc65-2.16-opt     | 4003 |
|                         | cc65-2.18-unopt   | 30112 |
|                         | cc65-2.18-opt     | 4030 |
|                         | vbcc-0.9h-unopt   | 3315 |
|![](../images/96c1ee.png)| vbcc-0.9h-opt     | 2505 |
|                         | prog8-3.2         | 7272 |
|![](../images/ff7f27.png)| kickc-0.8.2       | 1994 |
|                         | basic-boss        | n/a |

_Notes:_

* _CC65 2.16 and CC65 2.18 generate the exact same code. The speed differences are probably due to linking layout differences._



![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:1754|1780|4003|2505|1994&chdl=asm|mfk-0.3.18-O4|cc65-2.16-opt|vbcc-0.9h-opt|kickc-0.8&chtt=Plasma%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=y,x&chco=404040,008000,aa0000,96c1ee,ff7f27&chxl=0:||&chds=0,50000&chxr=1,0,5000)


### Benchmark `fib`

Source: [`fib.c`](./fib.c), [`fib.mfk`](./fib.mfk), [`fib-asm.mfk`](./fib-asm.mfk)

The benchmark calculates the first 25 Fibonacci numbers using the naïve recursive algorithm.

Results:

|                         | symbol            | frames (less is better) |
|-|-|-:|
|![](../images/404040.png)| asm               | 1309 |
|                         | mfk-0.3.18-O1     | 2156 |
|![](../images/008000.png)| mfk-0.3.18-O4     | 1476 |
|                         | mfk-0.3.18-O4-ill | 1476 |
|![](../images/66e266.png)| mfk-0.3.18-O4-ss  | 1783 |
|                         | atalan-2011       | n/a |
|                         | cc65-2.16-unopt   | 4647 |
|![](../images/aa0000.png)| cc65-2.16-opt     | 3261 |
|                         | cc65-2.18-unopt   | 4647 |
|                         | cc65-2.18-opt     | 3261 |
|                         | vbcc-0.9h-unopt   | 2915 |
|![](../images/96c1ee.png)| vbcc-0.9h-opt     | 2401 |
|                         | prog8-3.2         | n/a |
|                         | kickc-0.8.2       | n/a |
|                         | basic-boss        | n/a |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:1309|1476|1783|3261|2401&chdl=asm|mfk-0.3.18-O4|mfk-0.3.18-O4-ss|cc65-2.16-opt|vbcc-0.9h-opt&chtt=Fibonacci%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=y,x&chco=404040,008000,66e266,aa0000,96c1ee&chxl=0:||&chds=0,4000&chxr=1,0,4000)


### Benchmark `linkedlist`

Source: [`linkedlist.c`](./linkedlist.c), [`linkedlist.mfk`](./linkedlist.mfk), [`linkedlist-kc.kc`](./linkedlist-kc.kc)

The benchmark creates a single-linked list with 3000 entries, with a 16-bit integer at each node, and then traverses the list and sums all the values together. It does it five times, for more precise results.
 

Results:

|                         | symbol            | frames (less is better) |
|-|-|-:|
|                         | asm               | n/a |
|                         | mfk-0.3.18-O1     | 236 |
|![](../images/008000.png)| mfk-0.3.18-O4     | 215 |
|                         | mfk-0.3.18-O4-ill | 212 |
|                         | mfk-0.3.18-O4-ss  | 216 |
|                         | atalan-2011       | n/a |
|                         | cc65-2.16-unopt   | 739 |
|![](../images/aa0000.png)| cc65-2.16-opt     | 396 |
|                         | cc65-2.18-unopt   | 739 |
|                         | cc65-2.18-opt     | 392 |
|                         | vbcc-0.9h-unopt   | 313 |
|![](../images/96c1ee.png)| vbcc-0.9h-opt     | 215 |
|                         | prog8-3.2         | n/a |
|![](../images/ff7f27.png)| kickc-0.8.2       | 279 |
|                         | basic-boss        | n/a |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:215|396|215|279&chdl=mfk-0.3.18-O4|cc65-2.16-opt|vbcc-0.9h-opt|kickc-0.8.2 &chtt=Linked%20list%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=y,x&chco=008000,aa0000,96c1ee,ff7f27&chxl=0:||&chds=0,500&chxr=1,0,500)

_Notes:_

* There's a performance regression in this benchmark in KickC 0.8.

### Benchmark `romsum`

Source: [`romsum.c`](./romsum.c), [`romsum.mfk`](./romsum.mfk), [`romsum-asm.mfk`](./romsum-asm.mfk), [`romsum-atl.atl`](./romsum-atl.atl), [`romsum-p8.p8`](./romsum-p8.p8), [`romsum-kc.kc`](./romsum-kc.kc)

The benchmark sums all the bytes in the Kernal ROM and prints their sum (as a 16-bit integer). The benchmark is repeated 6 times, for more precise results.

Results:

|                         | symbol            | frames (less is better) |
|-|-|-:|
|![](../images/404040.png)| asm               | 51   |
|                         | mfk-0.3.18-O1     | 81   |
|![](../images/008000.png)| mfk-0.3.18-O4     | 75   |
|                         | mfk-0.3.18-O4-ill | 75   |
|                         | mfk-0.3.18-O4-ss  | n/a  |
|![](../images/2200aa.png)| atalan-2011       | 96   |
|                         | cc65-2.16-unopt   | 310 |
|![](../images/aa0000.png)| cc65-2.16-opt     | 127  |
|                         | cc65-2.18-unopt   | 310 |
|                         | cc65-2.18-opt     | 127  |
|                         | vbcc-0.9h-unopt   | 161 |
|![](../images/96c1ee.png)| vbcc-0.9h-opt     | 161 |
|                         | prog8-3.2         | 456  |
|![](../images/ff7f27.png)| kickc-0.8.2       | 81   |
|                         | basic-boss        | n/a |

![](https://image-charts.com/chart?cht=bhg&chs=700x400&chd=t:51|75|127|161|81|96&chdl=asm|mfk-0.3.18-O4|cc65-2.16-opt|vbcc-0.9h-opt|kickc-0.8.2|atalan-2011&chtt=ROM%20sum%20benchmark%20(time%20in%20frames,%20less%20is%20better)&chma=10,10&chxt=y,x&chco=404040,008000,aa0000,96c1ee,ff7f27,2200aa&chxl=0:||&chds=0,500&chxr=1,0,200)
