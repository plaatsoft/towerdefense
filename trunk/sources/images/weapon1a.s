.rodata
.balign 32
.globl pic506length
.globl pic506data

pic506length:	.long	picdataend - pic506data
pic506data:
.incbin "../images/weapon1a.png"
picdataend:


