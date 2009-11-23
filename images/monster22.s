.rodata
.balign 32
.globl pic122length
.globl pic122data

pic122length:	.long	picdataend - pic122data
pic122data:
.incbin "../images/monster22.png"
picdataend:


