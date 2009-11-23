.rodata
.balign 32
.globl pic305length
.globl pic305data

pic305length:	.long	picdataend - pic305data
pic305data:
.incbin "../images/base5.png"
picdataend:


