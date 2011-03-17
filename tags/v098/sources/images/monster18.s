.rodata
.balign 32
.globl pic118length
.globl pic118data

pic118length:	.long	picdataend - pic118data
pic118data:
.incbin "../images/monster18.png"
picdataend:


