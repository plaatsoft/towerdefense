.rodata
.balign 32
.globl pic302length
.globl pic302data

pic302length:	.long	picdataend - pic302data
pic302data:
.incbin "../images/base2.png"
picdataend:


