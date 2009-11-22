.rodata
.balign 32
.globl pic44length
.globl pic44data

pic44length:	.long	picdataend - pic44data
pic44data:
.incbin "../images/logo2.jpg"
picdataend:


