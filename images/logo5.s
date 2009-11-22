.rodata
.balign 32
.globl pic47length
.globl pic47data

pic47length:	.long	picdataend - pic47data
pic47data:
.incbin "../images/logo5.jpg"
picdataend:


