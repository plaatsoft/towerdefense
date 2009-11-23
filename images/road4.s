.rodata
.balign 32
.globl pic404length
.globl pic404data

pic404length:	.long	picdataend - pic404data
pic404data:
.incbin "../images/road4.png"
picdataend:


