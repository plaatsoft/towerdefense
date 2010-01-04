.rodata
.balign 32
.globl pic151length
.globl pic151data

pic151length:	.long	picdataend - pic151data
pic151data:
.incbin "../images/monster1a.png"
picdataend:


