.rodata
.balign 32
.globl pic102length
.globl pic102data

pic102length:	.long	picdataend - pic102data
pic102data:
.incbin "../images/monster2.png"
picdataend:


