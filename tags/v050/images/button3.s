.rodata
.balign 32
.globl pic604length
.globl pic604data

pic604length:	.long	picdataend - pic604data
pic604data:
.incbin "../images/button3.png"
picdataend:


