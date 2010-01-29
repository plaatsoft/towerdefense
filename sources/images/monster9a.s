.rodata
.balign 32
.globl pic159length
.globl pic159data

pic159length:	.long	picdataend - pic159data
pic159data:
.incbin "../images/monster9a.png"
picdataend:


