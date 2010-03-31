.rodata
.balign 32
.globl pic119length
.globl pic119data

pic119length:	.long	picdataend - pic119data
pic119data:
.incbin "../images/monster19.png"
picdataend:


