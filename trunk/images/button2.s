.rodata
.balign 32
.globl pic602length
.globl pic602data

pic602length:	.long	picdataend - pic602data
pic602data:
.incbin "../images/button2.png"
picdataend:


