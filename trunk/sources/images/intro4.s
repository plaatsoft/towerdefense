.rodata
.balign 32
.globl pic1000length
.globl pic1000data

pic1000length:	.long	picdataend - pic1000data
pic1000data:
.incbin "../images/intro4.jpg"
picdataend:


