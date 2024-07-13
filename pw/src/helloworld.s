/* vim: set ft=gas: */

.include "pwio.inc"
.include "flashrom.inc"
.include "ramvars.inc"

.section ".text.entry", "ax", %progbits
.type _start, %function
.global _start
_start:
	jsr common_prologue
	jsr wdt_pet

	/* first, disable any chipsel stuff */
	/*mov.b #0xff, r0l
	mov.b r0l, @PDR1
	mov.b r0l, @PDR9*/

	# SSU TX only
#	mov.b #0x80, r0l
#	mov.b r0l, @SSER

	/*# lcd chipsel
	bclr #0, @PDR1:8
	# lcd cmds
	bclr #1, @PDR1:8*/

	# above is done by this fn
	jsr lcdExitPowerSaveMode

	mov.w #cmd_data, r2
6:	mov.b @er2, r0l
	jsr lcdSendSingleByteCommand
	inc.w #1, r2
	cmp #cmd_data_end, r2
	bne 6b

	# lcd data
	bset #1, @PDR1:8

	mov.w #ttnlogo, r2
8:	mov.b @er2, r0l
	jsr lcdSendSingleByteCommand
	mov.b @er2, r0l
	jsr lcdSendSingleByteCommand
	inc.w #1, r2
	cmp #ttnlogo_end, r2
	bne 8b

/*	mov.w #0xf000, r3
4:	mov.b r3h, r0l
	jsr lcdSendSingleByteCommand
	mov.b r3h, r0l
	jsr lcdSendSingleByteCommand
	dec.b r3h
	# xor #0xff, r3h
	dec.b r3l
	bne 4b*/

	mov.b #0xc0, r0l
3:	push.w r0
	jsr smallDelay
	jsr wdt_pet
	pop.w r0
	dec.b r0l
	bne 3b

2:	mov.w #irCommsEventLoop, r0
	jsr setEventLoopFunc
	jmp common_epilogue

/*send_byte:
	mov.b @SSSR, r0h
	bld #2, r0h
	bcc send_byte
	mov.b r0l, @SSTDR
	rts*/

cmd_data:
	.byte 0x00
	.byte 0x10
	.byte 0x18
	# .byte 0x40,0x00
	# .byte 0x44,0x00
	.byte 0xaf
	.byte 0xb0,0x00
	.byte 0xa4
cmd_data_end:

ttnlogo:
	# pre-t
	# .byte 0x40,0x60,0x60,0,0
	.byte 0x02,0x06,0x06,0/*,0*/
	# t
	# .byte 0x60,0x60,0x7f,0x7e
	.byte 0x06,0x06,0xfe,0x7e
	# i
	# .byte 0x60,0x60,0xe6,0xee
	.byte 0x06,0x06,0x67,0x77
	# t
	# .byte 0x60,0x60,0x7f,0x7e
	.byte 0x06,0x06,0xfe,0x7e
	# a
	# .byte 0x60,0x62,0x7f,0x32,0x1a,0x0e
	.byte 0x06,0x46,0xfe,0x4c,0x58,0x70
	# n
	# .byte 0x46,0x7e,0x7e,0x30,0x18,0x0a,0x7e,0x7f,0x40
	.byte 0x62,0x7e,0x7e,0x0c,0x18,0x50,/*0x7e,*/0xfe,0xfe,0x02
ttnlogo_end:

