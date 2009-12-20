.rodata
.balign 32
.globl pic123length
.globl pic123data

pic123length:	.long	picdataend - pic123data
pic123data:
.incbin "../images/monster23.png"
picdataend:


