.rodata
.balign 32
.globl pic46length
.globl pic46data

pic46length:	.long	picdataend - pic46data
pic46data:
.incbin "../images/logo4.jpg"
picdataend:


