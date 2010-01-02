.rodata
.balign 32
.globl pic104length
.globl pic104data

pic104length:	.long	picdataend - pic104data
pic104data:
.incbin "../images/monster4.png"
picdataend:


