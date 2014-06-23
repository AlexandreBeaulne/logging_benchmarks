
Quick microbenchmarks of writing to file vs writing to socket on Unix machine.

```
Distro:       #64~precise1-Ubuntu
Architecture: x86_64
CPU Model:    Intel(R) Core(TM)2 CPU         T5600  @ 1.83GHz
# CPUs:       2
RAM:          1525696 kB
Network Card: Intel Corporation PRO/Wireless 3945ABG [Golan] Network Connection (rev 02)

Writing 100000 logs to file took 67354504 nanoseconds.
Writing 100000 logs to UDP socket took 1661525388 nanoseconds.
```

