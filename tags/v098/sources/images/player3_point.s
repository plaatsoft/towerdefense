.rodata
.balign 32
.globl pic202length
.globl pic202data

pic202length:	.long	picdataend - pic202data
pic202data:
.incbin "../images/player3_point.png"
picdataend:


