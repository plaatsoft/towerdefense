.rodata
.balign 32
.globl pic164length
.globl pic164data

pic164length:	.long	picdataend - pic164data
pic164data:
.incbin "../images/monster14a.png"
picdataend:


