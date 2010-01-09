.rodata
.balign 32
.globl pic107length
.globl pic107data

pic107length:	.long	picdataend - pic107data
pic107data:
.incbin "../images/monster7.png"
picdataend:


