/*---------------------------------------------------------------------------------

	default ARM7 core

		Copyright (C) 2005 - 2010
		Michael Noland (joat)
		Jason Rogers (dovoto)
		Dave Murphy (WinterMute)

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any
	damages arising from the use of this software.

	Permission is granted to anyone to use this software for any
	purpose, including commercial applications, and to alter it and
	redistribute it freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you
		must not claim that you wrote the original software. If you use
		this software in a product, an acknowledgment in the product
		documentation would be appreciated but is not required.

	2.	Altered source versions must be plainly marked as such, and
		must not be misrepresented as being the original software.

	3.	This notice may not be removed or altered from any source
		distribution.

---------------------------------------------------------------------------------*/
#include <nds.h>

// #include "nwram.h"

volatile static bool exitflag = false;

static void VblankHandler(void) {
}

static void VcountHandler() {
	inputGetAndSend();
}

static void powerButtonCB() {
	exitflag = true;
}

int main() {
	// REG_MBK_PROT=0;//allow ARM9 rw

	// clear sound registers
	dmaFillWords(0, (void*)0x04000400, 0x100);
	REG_SOUNDCNT |= SOUND_ENABLE;
	writePowerManagement(PM_CONTROL_REG, (readPowerManagement(PM_CONTROL_REG) & ~PM_SOUND_MUTE) | PM_SOUND_AMP);
	powerOn(POWER_SOUND);

	readUserSettings();
	ledBlink(0);

	irqInit();
	// Start the RTC tracking IRQ
	initClockIRQ();
	fifoInit();
	//touchInit();

	//mmInstall(FIFO_MAXMOD);

	SetYtrigger(80);

	//installWifiFIFO();
	installSoundFIFO();
	installSystemFIFO();

	irqSet(IRQ_VCOUNT, VcountHandler);
	irqSet(IRQ_VBLANK, VblankHandler);

	irqEnable( IRQ_VBLANK | IRQ_VCOUNT /*| IRQ_NETWORK*/);

	if (isDSiMode()) {
		irqEnableAUX(IRQ_I2C);
		setPowerButtonCB(powerButtonCB);
	}

	ledBlink(0);

	// Keep the ARM7 mostly idle
	while (!exitflag) {
		if (!(REG_KEYINPUT & (KEY_SELECT | KEY_START | KEY_L | KEY_R))) {
			exitflag = true;
		}
		swiWaitForVBlank();
	}
	return 0;
}

