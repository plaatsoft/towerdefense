.rodata
.balign 32
.globl pic174length
.globl pic174data

pic174length:	.long	picdataend - pic174data
pic174data:
.incbin "../images/monster24a.png"
picdataend:


