.rodata
.balign 32
.globl pic203length
.globl pic203data

pic203length:	.long	picdataend - pic203data
pic203data:
.incbin "../images/player4_point.png"
picdataend:


