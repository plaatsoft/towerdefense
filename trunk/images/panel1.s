.rodata
.balign 32
.globl pic13length
.globl pic13data

pic13length:	.long	picdataend - pic13data
pic13data:
.incbin "../images/panel1.png"
picdataend:


