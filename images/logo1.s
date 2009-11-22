.rodata
.balign 32
.globl pic43length
.globl pic43data

pic43length:	.long	picdataend - pic43data
pic43data:
.incbin "../images/logo1.jpg"
picdataend:


