.rodata
.balign 32
.globl pic105length
.globl pic105data

pic105length:	.long	picdataend - pic105data
pic105data:
.incbin "../images/monster5.png"
picdataend:


