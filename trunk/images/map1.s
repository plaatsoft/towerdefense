.rodata
.balign 32
.globl pic700length
.globl pic700data

pic700length:	.long	picdataend - pic700data
pic700data:
.incbin "../images/map1.png"
picdataend:


