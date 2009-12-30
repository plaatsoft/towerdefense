.rodata
.balign 32
.globl pic106length
.globl pic106data

pic106length:	.long	picdataend - pic106data
pic106data:
.incbin "../images/monster6.png"
picdataend:


