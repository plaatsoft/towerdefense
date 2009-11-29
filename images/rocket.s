.rodata
.balign 32
.globl pic500length
.globl pic500data

pic500length:	.long	picdataend - pic500data
pic500data:
.incbin "../images/road5.png"
picdataend:


