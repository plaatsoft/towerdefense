.rodata
.balign 32
.globl pic100length
.globl pic100data

pic100length:	.long	picdataend - pic100data
pic100data:
.incbin "../images/monster1.png"
picdataend:


