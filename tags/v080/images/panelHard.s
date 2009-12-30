.rodata
.balign 32
.globl pic22length
.globl pic22data

pic22length:	.long	picdataend - pic22data
pic22data:
.incbin "../images/panelHard.png"
picdataend:


