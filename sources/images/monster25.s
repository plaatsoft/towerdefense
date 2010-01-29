.rodata
.balign 32
.globl pic125length
.globl pic125data

pic125length:	.long	picdataend - pic125data
pic125data:
.incbin "../images/monster25.png"
picdataend:


