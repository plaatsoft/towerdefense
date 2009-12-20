.rodata
.balign 32
.globl pic117length
.globl pic117data

pic117length:	.long	picdataend - pic117data
pic117data:
.incbin "../images/monster17.png"
picdataend:


