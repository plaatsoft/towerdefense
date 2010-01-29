.rodata
.balign 32
.globl pic509length
.globl pic509data

pic509length:	.long	picdataend - pic509data
pic509data:
.incbin "../images/weapon4a.png"
picdataend:


