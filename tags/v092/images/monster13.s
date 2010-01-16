.rodata
.balign 32
.globl pic113length
.globl pic113data

pic113length:	.long	picdataend - pic113data
pic113data:
.incbin "../images/monster13.png"
picdataend:


