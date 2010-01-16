.rodata
.balign 32
.globl pic115length
.globl pic115data

pic115length:	.long	picdataend - pic115data
pic115data:
.incbin "../images/monster15.png"
picdataend:


