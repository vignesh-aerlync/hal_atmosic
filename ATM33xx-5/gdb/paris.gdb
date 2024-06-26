mem 0x00000000 0x00090000 ro
mem 0x10000000 0x10090000 ro
mem 0x20000000 0x20020000 rw
mem 0x30000000 0x30020000 rw

mem 0x40000000 0x40128000 rw 32
mem 0x40128000 0x40130000 rw
mem 0x40140000 0x40171000 rw 32
mem 0x40300000 0x40302000 rw
mem 0x40304000 0x40305000 rw

mem 0x50000000 0x50128000 rw 32
mem 0x50128000 0x50130000 rw
mem 0x50140000 0x50171000 rw 32
mem 0x50300000 0x50302000 rw
mem 0x50304000 0x50305000 rw

mem 0x00200000 0x01200000 ro
mem 0x10200000 0x11200000 ro

mem 0xe0000000 0xe0100000 rw 32
set remote hardware-breakpoint-limit 8
set remote hardware-watchpoint-limit 4