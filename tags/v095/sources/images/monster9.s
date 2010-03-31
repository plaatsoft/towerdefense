.rodata
.balign 32
.globl pic109length
.globl pic109data

pic109length:	.long	picdataend - pic109data
pic109data:
.incbin "../images/monster9.png"
picdataend:


