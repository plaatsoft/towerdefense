.rodata
.balign 32
.globl pic168length
.globl pic168data

pic168length:	.long	picdataend - pic168data
pic168data:
.incbin "../images/monster18a.png"
picdataend:


