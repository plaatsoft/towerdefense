.rodata
.balign 32
.globl pic162length
.globl pic162data

pic162length:	.long	picdataend - pic162data
pic162data:
.incbin "../images/monster12a.png"
picdataend:


