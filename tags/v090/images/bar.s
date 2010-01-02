.rodata
.balign 32
.globl pic14length
.globl pic14data

pic14length:	.long	picdataend - pic14data
pic14data:
.incbin "../images/bar.png"
picdataend:


