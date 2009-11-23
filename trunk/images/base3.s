.rodata
.balign 32
.globl pic303length
.globl pic303data

pic303length:	.long	picdataend - pic303data
pic303data:
.incbin "../images/base3.png"
picdataend:


