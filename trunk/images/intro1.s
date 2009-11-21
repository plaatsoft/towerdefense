.rodata
.balign 32
.globl pic1length
.globl pic1data

pic1length:	.long	picdataend - pic1data
pic1data:
.incbin "../images/intro1.jpg"
picdataend:


