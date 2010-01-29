.rodata
.balign 32
.globl pic152length
.globl pic152data

pic152length:	.long	picdataend - pic152data
pic152data:
.incbin "../images/monster2a.png"
picdataend:


