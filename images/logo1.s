.rodata
.balign 32
.globl pic4length
.globl pic4data

pic4length:	.long	picdataend - pic4data
pic4data:
.incbin "../images/logo1.png"
picdataend:


