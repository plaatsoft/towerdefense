.rodata
.balign 32
.globl pic49length
.globl pic49data

pic49length:	.long	picdataend - pic49data
pic49data:
.incbin "../images/logo6.jpg"
picdataend:


