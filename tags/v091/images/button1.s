.rodata
.balign 32
.globl pic600length
.globl pic600data

pic600length:	.long	picdataend - pic600data
pic600data:
.incbin "../images/button1.png"
picdataend:


