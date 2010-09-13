.rodata
.balign 32
.globl pic173length
.globl pic173data

pic173length:	.long	picdataend - pic173data
pic173data:
.incbin "../images/monster23a.png"
picdataend:


