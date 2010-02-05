.rodata
.balign 32
.globl pic504length
.globl pic504data

pic504length:	.long	picdataend - pic504data
pic504data:
.incbin "../images/weapon5.png"
picdataend:


