.rodata
.balign 32
.globl pic21length
.globl pic21data

pic21length:	.long	picdataend - pic21data
pic21data:
.incbin "../images/panelMedium.png"
picdataend:


