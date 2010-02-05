.rodata
.balign 32
.globl pic605length
.globl pic605data

pic605length:	.long	picdataend - pic605data
pic605data:
.incbin "../images/button3focus.png"
picdataend:


