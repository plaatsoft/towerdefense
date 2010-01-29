.rodata
.balign 32
.globl pic607length
.globl pic607data

pic607length:	.long	picdataend - pic607data
pic607data:
.incbin "../images/button4focus.png"
picdataend:


