.rodata
.balign 32
.globl pic108length
.globl pic108data

pic108length:	.long	picdataend - pic108data
pic108data:
.incbin "../images/monster8.png"
picdataend:


