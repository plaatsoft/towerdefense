.rodata
.balign 32
.globl pic101length
.globl pic101data

pic101length:	.long	picdataend - pic101data
pic101data:
.incbin "../images/monster1.png"
picdataend:


