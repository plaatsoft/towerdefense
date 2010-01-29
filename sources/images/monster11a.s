.rodata
.balign 32
.globl pic161length
.globl pic161data

pic161length:	.long	picdataend - pic161data
pic161data:
.incbin "../images/monster11a.png"
picdataend:


