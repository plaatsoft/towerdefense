.rodata
.balign 32
.globl pic169length
.globl pic169data

pic169length:	.long	picdataend - pic169data
pic169data:
.incbin "../images/monster19a.png"
picdataend:


