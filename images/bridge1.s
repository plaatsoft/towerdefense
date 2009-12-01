.rodata
.balign 32
.globl pic407length
.globl pic407data

pic407length:	.long	picdataend - pic407data
pic407data:
.incbin "../images/bridge1.png"
picdataend:


