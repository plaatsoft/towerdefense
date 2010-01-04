.rodata
.balign 32
.globl pic153length
.globl pic153data

pic153length:	.long	picdataend - pic153data
pic153data:
.incbin "../images/monster3a.png"
picdataend:


