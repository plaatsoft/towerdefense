.rodata
.balign 32
.globl pic304length
.globl pic304data

pic304length:	.long	picdataend - pic304data
pic304data:
.incbin "../images/base4.png"
picdataend:


