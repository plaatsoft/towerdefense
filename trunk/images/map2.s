.rodata
.balign 32
.globl pic701length
.globl pic701data

pic701length:	.long	picdataend - pic701data
pic701data:
.incbin "../images/map2.png"
picdataend:


