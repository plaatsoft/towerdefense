.rodata
.balign 32
.globl pic606length
.globl pic606data

pic606length:	.long	picdataend - pic606data
pic606data:
.incbin "../images/button4.png"
picdataend:


