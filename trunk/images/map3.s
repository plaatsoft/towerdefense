.rodata
.balign 32
.globl pic702length
.globl pic702data

pic702length:	.long	picdataend - pic702data
pic702data:
.incbin "../images/map3.png"
picdataend:


