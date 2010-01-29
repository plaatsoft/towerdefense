.rodata
.balign 32
.globl pic16length
.globl pic16data

pic16length:	.long	picdataend - pic16data
pic16data:
.incbin "../images/soundicon.png"
picdataend:


