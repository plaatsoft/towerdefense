.rodata
.balign 32
.globl pic306length
.globl pic306data

pic306length:	.long	picdataend - pic306data
pic306data:
.incbin "../images/base6.png"
picdataend:


