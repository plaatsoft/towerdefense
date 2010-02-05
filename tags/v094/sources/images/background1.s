.rodata
.balign 32
.globl pic10length
.globl pic10data

pic10length:	.long	picdataend - pic10data
pic10data:
.incbin "../images/background1.jpg"
picdataend:


