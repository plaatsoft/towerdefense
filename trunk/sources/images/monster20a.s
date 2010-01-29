.rodata
.balign 32
.globl pic170length
.globl pic170data

pic170length:	.long	picdataend - pic170data
pic170data:
.incbin "../images/monster20a.png"
picdataend:


