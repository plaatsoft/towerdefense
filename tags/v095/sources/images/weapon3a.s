.rodata
.balign 32
.globl pic508length
.globl pic508data

pic508length:	.long	picdataend - pic508data
pic508data:
.incbin "../images/weapon3a.png"
picdataend:


