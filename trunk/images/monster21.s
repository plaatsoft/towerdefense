.rodata
.balign 32
.globl pic121length
.globl pic121data

pic121length:	.long	picdataend - pic121data
pic121data:
.incbin "../images/monster21.png"
picdataend:


