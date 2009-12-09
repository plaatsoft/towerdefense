.rodata
.balign 32
.globl pic603length
.globl pic603data

pic603length:	.long	picdataend - pic603data
pic603data:
.incbin "../images/button2focus.png"
picdataend:


