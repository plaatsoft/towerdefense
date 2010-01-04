.rodata
.balign 32
.globl pic156length
.globl pic156data

pic156length:	.long	picdataend - pic156data
pic156data:
.incbin "../images/monster6a.png"
picdataend:


