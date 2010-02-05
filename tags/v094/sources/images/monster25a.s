.rodata
.balign 32
.globl pic175length
.globl pic175data

pic175length:	.long	picdataend - pic175data
pic175data:
.incbin "../images/monster25a.png"
picdataend:


