.rodata
.balign 32
.globl pic112length
.globl pic112data

pic112length:	.long	picdataend - pic112data
pic112data:
.incbin "../images/monster12.png"
picdataend:


