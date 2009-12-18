.rodata
.balign 32
.globl pic110length
.globl pic110data

pic110length:	.long	picdataend - pic110data
pic110data:
.incbin "../images/monster10.png"
picdataend:


