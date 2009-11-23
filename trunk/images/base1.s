.rodata
.balign 32
.globl pic301length
.globl pic301data

pic301length:	.long	picdataend - pic301data
pic301data:
.incbin "../images/base1.png"
picdataend:


