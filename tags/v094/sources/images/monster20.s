.rodata
.balign 32
.globl pic120length
.globl pic120data

pic120length:	.long	picdataend - pic120data
pic120data:
.incbin "../images/monster20.png"
picdataend:


