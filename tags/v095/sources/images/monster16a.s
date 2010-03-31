.rodata
.balign 32
.globl pic166length
.globl pic166data

pic166length:	.long	picdataend - pic166data
pic166data:
.incbin "../images/monster16a.png"
picdataend:


