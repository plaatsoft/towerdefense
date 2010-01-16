.rodata
.balign 32
.globl pic33length
.globl pic33data

pic33length:	.long	picdataend - pic33data
pic33data:
.incbin "../images/scrollbar.png"
picdataend:


