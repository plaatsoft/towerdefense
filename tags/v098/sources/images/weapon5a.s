.rodata
.balign 32
.globl pic510length
.globl pic510data

pic510length:	.long	picdataend - pic510data
pic510data:
.incbin "../images/weapon5a.png"
picdataend:


