.rodata
.balign 32
.globl pic154length
.globl pic154data

pic154length:	.long	picdataend - pic154data
pic154data:
.incbin "../images/monster4a.png"
picdataend:


