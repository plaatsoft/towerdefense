.rodata
.balign 32
.globl pic403length
.globl pic403data

pic403length:	.long	picdataend - pic403data
pic403data:
.incbin "../images/road3.png"
picdataend:


