1 rem@ \word j,i: \byte si(: \constant co,sc
2 rem@ \fastarray: \fastfor
10 co=16384: sc=128
11 dim si(co)
20 t0=ti
40 gosub 100:gosub 100:gosub 100:gosub 100:gosub 100
45 gosub 100:gosub 100:gosub 100:gosub 100:gosub 100
50 t1=ti
60 print t1-t0
99 end
100 for i=0 to co-1: si(i)=0: next i
110 for i=2 to sc-1
120 if si(i)<>0 then 130
123 for j=i*2 to co-1
124 si(j)=1: j=j+i
125 next j
130 next i
140 return
