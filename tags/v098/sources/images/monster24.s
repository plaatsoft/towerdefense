.rodata
.balign 32
.globl pic124length
.globl pic124data

pic124length:	.long	picdataend - pic124data
pic124data:
.incbin "../images/monster24.png"
picdataend:


