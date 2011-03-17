.rodata
.balign 32
.globl pic171length
.globl pic171data

pic171length:	.long	picdataend - pic171data
pic171data:
.incbin "../images/monster21a.png"
picdataend:


