.rodata
.balign 32
.globl pic502length
.globl pic502data

pic502length:	.long	picdataend - pic502data
pic502data:
.incbin "../images/weapon3.png"
picdataend:


