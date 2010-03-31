.rodata
.balign 32
.globl pic114length
.globl pic114data

pic114length:	.long	picdataend - pic114data
pic114data:
.incbin "../images/monster14.png"
picdataend:


