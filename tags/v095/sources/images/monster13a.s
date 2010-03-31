.rodata
.balign 32
.globl pic163length
.globl pic163data

pic163length:	.long	picdataend - pic163data
pic163data:
.incbin "../images/monster13a.png"
picdataend:


