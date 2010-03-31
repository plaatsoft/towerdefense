.rodata
.balign 32
.globl pic505length
.globl pic505data

pic505length:	.long	picdataend - pic505data
pic505data:
.incbin "../images/weapon6.png"
picdataend:


