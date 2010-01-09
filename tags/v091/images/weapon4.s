.rodata
.balign 32
.globl pic503length
.globl pic503data

pic503length:	.long	picdataend - pic503data
pic503data:
.incbin "../images/weapon4.png"
picdataend:


