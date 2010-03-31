.rodata
.balign 32
.globl pic165length
.globl pic165data

pic165length:	.long	picdataend - pic165data
pic165data:
.incbin "../images/monster15a.png"
picdataend:


