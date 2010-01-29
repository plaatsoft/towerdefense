.rodata
.balign 32
.globl pic160length
.globl pic160data

pic160length:	.long	picdataend - pic160data
pic160data:
.incbin "../images/monster10a.png"
picdataend:


