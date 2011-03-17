.rodata
.balign 32
.globl pic157length
.globl pic157data

pic157length:	.long	picdataend - pic157data
pic157data:
.incbin "../images/monster7a.png"
picdataend:


