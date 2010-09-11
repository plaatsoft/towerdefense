.rodata
.balign 32
.globl pic111length
.globl pic111data

pic111length:	.long	picdataend - pic111data
pic111data:
.incbin "../images/monster11.png"
picdataend:


