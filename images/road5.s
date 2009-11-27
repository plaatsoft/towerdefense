.rodata
.balign 32
.globl pic405length
.globl pic405data

pic405length:	.long	picdataend - pic405data
pic405data:
.incbin "../images/road5.png"
picdataend:


