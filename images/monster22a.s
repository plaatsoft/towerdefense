.rodata
.balign 32
.globl pic172length
.globl pic172data

pic172length:	.long	picdataend - pic172data
pic172data:
.incbin "../images/monster22a.png"
picdataend:


