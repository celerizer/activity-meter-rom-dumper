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
	jsr smallDelay
	jsr wdt_pet
	jsr smallDelay
	jsr wdt_pet
	jsr smallDelay
	jsr wdt_pet

	sub.w r5, r5                           /* memcpy src (0) */
1:	mov.w #TX_PACKET_payload, r6           /* memcpy dest */
	mov.b #0x80, r4l                       /* memcpy length */
	eepmov.b                               /* memcpy */

	mov.w #0x3c80, r0                      /* packet: cmd=0x3c,len=0x80 */
	jsr sendPacket
	jsr smallDelay
	jsr wdt_pet
	jsr smallDelay
	cmp.w #0xc000, r5                      /* total size dumped */
	bne 1b

	mov.w #irCommsEventLoop, r0
	jsr setEventLoopFunc
	jmp common_epilogue

