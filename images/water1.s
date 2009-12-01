.rodata
.balign 32
.globl pic406length
.globl pic406data

pic406length:	.long	picdataend - pic406data
pic406data:
.incbin "../images/water1.png"
picdataend:


