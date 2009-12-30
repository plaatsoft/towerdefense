.rodata
.balign 32
.globl pic103length
.globl pic103data

pic103length:	.long	picdataend - pic103data
pic103data:
.incbin "../images/monster3.png"
picdataend:


