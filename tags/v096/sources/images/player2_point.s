.rodata
.balign 32
.globl pic201length
.globl pic201data

pic201length:	.long	picdataend - pic201data
pic201data:
.incbin "../images/player2_point.png"
picdataend:


