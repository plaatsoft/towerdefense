.rodata
.balign 32
.globl pic511length
.globl pic511data

pic511length:	.long	picdataend - pic511data
pic511data:
.incbin "../images/weapon6a.png"
picdataend:


