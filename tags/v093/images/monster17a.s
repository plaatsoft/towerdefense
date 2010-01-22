.rodata
.balign 32
.globl pic167length
.globl pic167data

pic167length:	.long	picdataend - pic167data
pic167data:
.incbin "../images/monster17a.png"
picdataend:


