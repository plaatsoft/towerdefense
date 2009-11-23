.rodata
.balign 32
.globl pic401length
.globl pic401data

pic401length:	.long	picdataend - pic401data
pic401data:
.incbin "../images/road1.png"
picdataend:


