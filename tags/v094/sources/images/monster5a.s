.rodata
.balign 32
.globl pic155length
.globl pic155data

pic155length:	.long	picdataend - pic155data
pic155data:
.incbin "../images/monster5a.png"
picdataend:


