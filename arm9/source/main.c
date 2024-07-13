
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <nds.h>
#include <fat.h>

#include "auxspi.h"
#include "ir.h"
#include "pw.h"

static const uint8_t rom_dump_sploit[] = { // write to 0xf956
	0x5e,0x00,0xba,0x42, // jsr common_prologue
	0x5e,0x00,0x25,0x9e, // jsr wdt_pet
	0x5e,0x00,0x7b,0x64, // jsr smallDelay
	0x5e,0x00,0x25,0x9e, // jsr wdt_pet
	0x5e,0x00,0x7b,0x64, // jsr smallDelay
	0x5e,0x00,0x25,0x9e, // jsr wdt_pet
	0x5e,0x00,0x7b,0x64, // jsr smallDelay
	0x5e,0x00,0x25,0x9e, // jsr wdt_pet
	0x19,0x55,           // sub.w  r5, r5    // memcpy source

//big_loop:
	0x79,0x06,0xf8,0xd6, // mov.w 0xf8d6, r6 // memcpy dest: packet payload buffer
	0xfc,0x80,           // mov.b 0x80, r4l  // memcpy length
	0x7b,0x5c,0x59,0x8f, // eemov.b          // memcpy
	0x79,0x00,0x3c,0x80, // mov.w 0x3c80, r0 // payload len=80h, cmd=3ch
	0x5e,0x00,0x07,0x72, // jsr sendPacket
	0x5e,0x00,0x7b,0x64, // jsr smallDelay
	0x5e,0x00,0x25,0x9e, // jsr wdt_pet
	0x5e,0x00,0x7b,0x64, // jsr smallDelay
	0x79,0x25,0xc0,0x00, // cmp.w r5, 0xc000
	0x46,0xdc,           // bne big_loop

	0x79,0x00,0x08,0xd6, // mov.w irHandleRxedByteIfAnyHasBeenRxed, r0
	0x5e,0x00,0x69,0x3a, // jsr setProcToCallbyMainLoop
	0x5a,0x00,0xba,0x62, // jmp common_epilogue
};
static const uint8_t sploit_trigger[] = { 0xf9,0x56 }; // write to f7e0
uint8_t flashrom_dump[0xc000];

int main(void) {
	consoleDemoInit();

	bool hasfat = fatInitDefault();
	if (!hasfat) {
		iprintf("can't init fat -> won't dump ROM\n");
	} else {
		iprintf("inited fat\n");
	}

	uint32_t v32v;
	uint8_t vvv;

	uint32_t keys = 0, oldkeys = 0;

	bool run = true;
	enum auxspi_extra extra;
	uint8_t savetype;

	if (!(run = auxspi_init_ir(true, &extra, &savetype))) {
		iprintf("IR init failed. will now hang\n");
		run = false;
		goto END;
	}
	iprintf("hello!\n");

	auxspi_read_data(0, (uint8_t*)&v32v, 4, 3, AUXSPI_INFRARED);
	iprintf("save flash hdr: %08lx\n", v32v);
	vvv = auxspi_save_status_register(AUXSPI_INFRARED);
	iprintf("sreg: %02x\n", vvv);

	ir_init();
	iprintf("Press A no balls\n\n");

	pw_poll_tries = 0x10;
	pw_poll_wait = pw_poll_wait_default;

END:;
	while (1) {
		scanKeys();
		oldkeys = keys;
		keys = keysDown();

		if (run && (keys & KEY_A) && !(oldkeys & KEY_A))
    {
			while (!pw_scan());

				iprintf("ping!\n");
        uint8_t buf[32];

				FILE* fff = fopen("sd:/wwmfull.rom", "wb");
				if (!fff)
					iprintf("can't open file :(\n");

				for (size_t i = 0; i < 0x10000; i += 32)
				{
          wwm_syn(i, 32);
				
				  if (!wwm_ack(buf))
				    iprintf("fail\n");

					iprintf("reading wwm rom (%04X)\n", i);
					fwrite(buf, 32, 1, fff);
				}
        fclose(fff);
        
		}

		if (run && (keys & KEY_X) && !(oldkeys & KEY_X)) {
			if (pw_scan()) {
				iprintf("ping!\n");

				uint32_t sessid;
				if (pw_do_synack(&sessid)) {
					//iprintf("got sess! %08lx\n", sessid);

					// EEPROM dumper
					FILE* fff = fopen("sd:/pweep.rom", "wb");
					if (!fff) {
						iprintf("can't open file :(\n");
						goto Lnop;
					}

					for (size_t i = 0; i < 512; ++i)
          {
						uint8_t mwahah[0x80];

						if (pw_read_eeprom(sessid, i*sizeof mwahah, sizeof mwahah, mwahah)) {
							iprintf("reading eeprom (%3d/512)\n", i+1);
						} else {
							iprintf("read failed :/\n");
							break;
						}
						fwrite(mwahah, sizeof mwahah, 1, fff);
					}
					fclose(fff);
					//fatUnmount("sd:");

				Lnop:
					if (pw_conn_end(sessid)) iprintf("closed correctly\n");
					else iprintf("welp\n");
				} else iprintf("can't connect\n");
			}
			else iprintf("no scan results\n");
		}

		if (run && (keys & KEY_Y) && !(oldkeys & KEY_Y)) {
			if (pw_scan()) {
				iprintf("ping!\n");

				uint32_t sessid;
				if (pw_do_synack(&sessid)) {
					//iprintf("got sess! %08lx\n", sessid);
					iprintf("WARN: doing untested stuff!\n");

					// EEPROM dumper
					FILE* fff = fopen("sd:/pweep.rom", "rb");
					if (!fff) {
						iprintf("can't open file :(\n");
						goto LnopY;
					}

					for (size_t i = 0; i < 1024; ++i) {
						uint8_t mwahah[0x40];
						if (fread(mwahah, sizeof mwahah, 1, fff) != 1) {
							iprintf("reading from SD file failed\n");
							fclose(fff);
							goto LnopY;
						}

						if (pw_write_eeprom(sessid, i*sizeof mwahah, sizeof mwahah, mwahah)) {
							iprintf("writing eeprom (%4d/1024)\n", i+1);
						} else {
							iprintf("write failed :/\n");
							break;
						}
						fwrite(mwahah, sizeof mwahah, 1, fff);
					}
					fclose(fff);
					//fatUnmount("sd:");

				LnopY:
					if (pw_conn_end(sessid)) iprintf("closed correctly\n");
					else iprintf("welp\n");
				} else iprintf("can't connect\n");
			}
			else iprintf("no scan results\n");
		}

		if (run && (keys & KEY_B) && !(oldkeys & KEY_B)) {
			if (pw_scan()) {
				iprintf("ping!\n");

				uint32_t sessid;
				if (pw_do_synack(&sessid)) {
					//iprintf("got sess! %08lx\n", sessid);

					if (!pw_write_mem(sessid, 0xf956, sizeof rom_dump_sploit,
								rom_dump_sploit)) {
						iprintf("can't install sploit\n");
						goto Lnop2;
					}
					if (!pw_write_mem(sessid, 0xf7e0, sizeof sploit_trigger,
								sploit_trigger)) {
						iprintf("can't install trigger\n");
						goto Lnop2;
					}
					iprintf("dumping!\n");
					for (ptrdiff_t size=0,nb; size < 0xc000; size += nb) {
						nb = pw_sploit_recv_dump_seg(sessid, &flashrom_dump[size]);
						if (nb < 0) {
							iprintf("dumping failed :/\n");
							break;
						}

						iprintf("dumping... (%04x/c000)\n", size);
					}
					iprintf("done!\n");
					FILE* fff = fopen("sd:/pwflash.rom","wb");
					if (!fff) {
						iprintf("can't open file\n");
					} else {
						fwrite(flashrom_dump, 1, 0xc000, fff);
						fclose(fff);
					}
				Lnop2:;
					if (pw_conn_end(sessid)) iprintf("closed correctly\n");
					else iprintf("welp\n");
				} else iprintf("can't connect\n");
			}
			else iprintf("no scan results\n");
		}

		if (run && (keys & KEY_L) && !(oldkeys & KEY_L)) {
			FILE* fff = fopen("sd:/cartflash.rom", "wb");
			if (!fff) {
				iprintf("can't open file :(\n");
				goto Lnop3;
			}

			for (size_t i = 0; i < (65536/256); ++i) {
				uint8_t mwahah[0x100];

				for (size_t j = 0; j < 256; ++j) {
					mwahah[j] = ir_cmd4(j | (i << 8));
				}
				iprintf("reading cart flash (%3d/256)\n", i+1);
				fwrite(mwahah, sizeof mwahah, 1, fff);
			}
			iprintf("done!\n");
			fclose(fff);
		Lnop3:;
		}

		if (run && (keys & KEY_R) && !(oldkeys & KEY_R)) {
			if (pw_scan()) {
				iprintf("ping!\n");

				uint32_t sessid;
				if (pw_do_synack(&sessid)) {
					//iprintf("got sess! %08lx\n", sessid);

					FILE* fff = fopen("sd:/pwcode.bin","rb");
					if (!fff) {
						iprintf("can't open file pwcode.bin\n");
						goto LnopL;
					}
					uint8_t stuff[0x200];
					size_t blobsize;
					if ((blobsize = fread(stuff, 1, sizeof stuff, fff)) <= 0) {
						iprintf("can't read file pwcode.bin\n");
						fclose(fff);
						goto LnopL;
					}
					fclose(fff);

					uint16_t org = 0xf8f0+0x180;
					uint16_t orgBE = ((org&0xff)<<8)|((org>>8)&0xff);
					size_t bloboff = 0;

					while (blobsize != 0) {
						size_t chunk = ((blobsize > 0x7e) ? 0x7e : blobsize);
						if (!pw_write_mem(sessid, org+bloboff, chunk, stuff+bloboff)) {
							iprintf("can't install code 0x%x\n", org);
							goto LnopL;
						}

						blobsize -= chunk;
						bloboff += chunk;
					}
					if (!pw_write_mem(sessid, 0xf7e0, sizeof sploit_trigger,
								&orgBE)) {
						iprintf("can't install trigger\n");
						goto LnopL;
					}
				LnopL:;
					if (pw_conn_end(sessid)) iprintf("closed correctly\n");
					else iprintf("welp\n");
				} else iprintf("can't connect\n");
			}
			else iprintf("no scan results\n");
		}

		if (keys & KEY_START) break;
		swiWaitForVBlank();
	}

	return 0;
}

