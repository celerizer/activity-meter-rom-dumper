
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <nds.h>

#include "auxspi.h"

#include "ir.h"

static bool lasthold = false;
bool auxspi_init_ir(bool wait_on_empty_slot, enum auxspi_extra* extra,
		uint8_t* savetype) {
	lasthold = false;

	//iprintf("SCFG EXT=0x%08lx\n", REG_SCFG_EXT);
	//iprintf("SCFG MC =0x%04x\n", REG_SCFG_MC);

	if (wait_on_empty_slot && isDSiMode() && (REG_SCFG_MC & 1)) {
		//iprintf("no cart\n");
		while (REG_SCFG_MC & 1) swiWaitForVBlank();
	}

	// AUXSPI to ARM9
	REG_EXMEMCNT &= ~(uint16_t)0x0800;

	if (isDSiMode()) {
		disableSlot1();
		for (int i = 0; i < 25; i++) swiWaitForVBlank();
		enableSlot1();
		for (int i = 0; i < 15; i++) swiWaitForVBlank();

		cardParamCommand(CARD_CMD_DUMMY, 0,
			CARD_ACTIVATE|CARD_nRESET|CARD_CLK_SLOW|CARD_BLK_SIZE(1)
				|CARD_DELAY1(0x1fff)|CARD_DELAY2(0x3f),
			NULL, 0);
	} else {
		REG_ROMCTRL = 0;
		REG_AUXSPICNT = 0;

		for (int i = 0; i < 25; i++) swiWaitForVBlank();

		REG_AUXSPICNT = CARD_CR1_ENABLE|CARD_CR1_IRQ;
		REG_ROMCTRL = CARD_nRESET|CARD_SEC_SEED;
		while (REG_ROMCTRL&CARD_BUSY) ;
		cardReset();
		while (REG_ROMCTRL&CARD_BUSY) ;
	}

	enum auxspi_extra ex;
	ex = auxspi_has_extra();
	if (extra) *extra = ex;

	//iprintf("auxspi extra=%d\n", ex);
	if (ex != AUXSPI_INFRARED) {
		//iprintf("not an IR cart!\n");
		return false;
	}

	if (savetype)
		*savetype = auxspi_save_type(ex);
	//iprintf("auxspi type=%hhu\n", *savetype);

	return true;
}

uint8_t auxspi_xfer_ir/*_base*/(uint8_t val, bool hold/*, bool reinit*/) {
	while (REG_AUXSPICNT & (1<<7)) ;

	if (lasthold != hold /*|| reinit*/) {
		if (hold) {
			REG_AUXSPICNT = 0xA040;
			swiDelay(1200);
			REG_AUXSPICNT = 0xA042;
		}
		else {
			REG_AUXSPICNT = 0xA000;
			swiDelay(1200);
			REG_AUXSPICNT = 0xA002;
		}
		lasthold = hold;
	}
	while (REG_AUXSPICNT & (1<<7)) ;
	swiDelay(1200);

	REG_AUXSPIDATA = val;
	while (REG_AUXSPICNT & (1<<7)) ;
	swiDelay(1200);
	return REG_AUXSPIDATA;
}

size_t ir_cmd1(uint8_t* rxbuf) {
	auxspi_xfer_ir(0x01, true);
	size_t size = auxspi_xfer_ir(0x00, true);

	if (!size) {
		// otherwise the following data will be eaten
		auxspi_xfer_ir(0x00, false);
	} else for (size_t i = 0; i < size; ++i) {
		uint8_t v = auxspi_xfer_ir(0x00, i < size-1);
		if (rxbuf) rxbuf[i] = v;
	}

	return size;
}
void ir_cmd2(size_t size, const uint8_t* buf) {
	auxspi_xfer_ir(0x02, true);

	for (size_t i = 0; i < size; ++i) {
		auxspi_xfer_ir(buf[i], i < size-1);
	}
}

uint8_t ir_cmd4(uint16_t addr) {
	auxspi_xfer_ir(0x04, true);

	auxspi_xfer_ir(addr >> 8, true);
	auxspi_xfer_ir(addr & 0xff, true);

	return auxspi_xfer_ir(0x00, false);
}

uint8_t ir_cmd8(void) {
	auxspi_xfer_ir(0x08, true);
	return auxspi_xfer_ir(0x00, false);
}

void ir_init(void) {
	size_t len = ir_cmd1(NULL);
	//if (len != 0) iprintf("W: weird cmd1 init len %zu\n", len);

	uint16_t stat = ir_stat();
	//if (stat != 0xaa00 && stat != 0xaaaa)
	//	iprintf("W: weird init stat %04x\n", stat);
}

