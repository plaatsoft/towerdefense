.rodata
.balign 32
.globl pic11length
.globl pic11data

pic11length:	.long	picdataend - pic11data
pic11data:
.incbin "../images/background2.png"
picdataend:


