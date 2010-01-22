.rodata
.balign 32
.globl pic507length
.globl pic507data

pic507length:	.long	picdataend - pic507data
pic507data:
.incbin "../images/weapon2a.png"
picdataend:


