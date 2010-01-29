.rodata
.balign 32
.globl pic601length
.globl pic601data

pic601length:	.long	picdataend - pic601data
pic601data:
.incbin "../images/button1focus.png"
picdataend:


