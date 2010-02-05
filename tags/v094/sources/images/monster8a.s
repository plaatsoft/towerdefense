.rodata
.balign 32
.globl pic158length
.globl pic158data

pic158length:	.long	picdataend - pic158data
pic158data:
.incbin "../images/monster8a.png"
picdataend:


