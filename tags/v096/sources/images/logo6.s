.rodata
.balign 32
.globl pic9length
.globl pic9data

pic9length:	.long	picdataend - pic9data
pic9data:
.incbin "../images/logo6.png"
picdataend:


