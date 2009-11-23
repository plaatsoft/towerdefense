.rodata
.balign 32
.globl pic402length
.globl pic402data

pic402length:	.long	picdataend - pic402data
pic402data:
.incbin "../images/road2.png"
picdataend:


