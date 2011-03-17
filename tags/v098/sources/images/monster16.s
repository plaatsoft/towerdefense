.rodata
.balign 32
.globl pic116length
.globl pic116data

pic116length:	.long	picdataend - pic116data
pic116data:
.incbin "../images/monster16.png"
picdataend:


