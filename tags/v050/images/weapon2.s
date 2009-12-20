.rodata
.balign 32
.globl pic501length
.globl pic501data

pic501length:	.long	picdataend - pic501data
pic501data:
.incbin "../images/weapon2.png"
picdataend:


