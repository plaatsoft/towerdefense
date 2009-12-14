.rodata
.balign 32
.globl pic703length
.globl pic703data

pic703length:	.long	picdataend - pic703data
pic703data:
.incbin "../images/map4.png"
picdataend:


