.rodata
.balign 32
.globl pic200length
.globl pic200data

pic200length:	.long	picdataend - pic200data
pic200data:
.incbin "../images/player1_point.png"
picdataend:


