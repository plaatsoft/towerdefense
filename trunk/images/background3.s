.rodata
.balign 32
.globl pic12length
.globl pic12data

pic12length:	.long	picdataend - pic12data
pic12data:
.incbin "../images/background3.jpg"
picdataend:


