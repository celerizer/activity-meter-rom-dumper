/*
 * savegame_manager: a tool to backup and restore savegames from Nintendo
 *  DS cartridges. Nintendo DS and all derivative names are trademarks
 *  by Nintendo. EZFlash 3-in-1 is a trademark by EZFlash.
 *
 * auxspi.cpp: A thin reimplementation of the AUXSPI protocol
 *   (high level functions)
 *
 * Copyright (C) Pokedoc (2010)
 */
/*
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <stdint.h>
#include <string.h>

#include <nds.h>

#include "auxspi.h"

inline static void auxspi_wait_busy(void) {
	while (REG_AUXSPICNT & 0x80) ;
}

inline static void auxspi_wait_wip(void) { // write in progress
	do {
		REG_AUXSPIDATA = 0;
		auxspi_wait_busy();
	} while (REG_AUXSPIDATA & 0x01);
}

inline static void auxspi_open(uint8_t device) {
	REG_AUXSPICNT = 0xa040 | (device & 3);
	auxspi_wait_busy();
}

inline static void auxspi_close(void) {
	REG_AUXSPIDATA = 0;
	auxspi_wait_busy();
	REG_AUXSPICNT = 0;
	auxspi_wait_busy();
}
inline static void auxspi_close_hold_chipsel(void) {
	REG_AUXSPICNT = 0x40;
	auxspi_wait_busy();
}

inline static uint8_t auxspi_transfer(uint8_t out) {
	REG_AUXSPIDATA = out;
	auxspi_wait_busy();
	return REG_AUXSPIDATA;
}

inline static void auxspi_write(uint8_t out) {
	auxspi_transfer(out);
}

inline static uint8_t auxspi_read(void) {
	return auxspi_transfer(0);
}

static uint8_t jedec_table(uint32_t id) {
	switch (id) {
	// 256 kB
	case 0x204012:
	case 0x621600:
		return 0x12;
	// 512 kB
	case 0x204013:
	case 0x621100:
		return 0x13;
	// 1 MB
	case 0x204014:
		return 0x14;
	// 2 MB (not sure if this exists, but I vaguely remember something...)
	case 0x204015:
		return 0x15;
	// 8 MB (Band Brothers DX)
	case 0x202017: // which one? (more work is required to unlock this save chip!)
	case 0x204017:
		return 0x17;
	}

	return 0; // unknown save type!
}

static uint8_t type2_size(enum auxspi_extra extra) {
	const uint32_t offset0 =   8*1024-1;
	const uint32_t offset1 = 2*8*1024-1;

	uint8_t buf1; // +0k data      read -> write
	uint8_t buf2; // +8k data      read -> read
	uint8_t buf3; // +0k ~data     write
	uint8_t buf4; // +8k data new  comp buf2
	auxspi_read_data(offset0, &buf1, 1, 2, extra);
	auxspi_read_data(offset1, &buf2, 1, 2, extra);
	buf3 = ~buf1;
	auxspi_write_data(offset0, &buf3, 1, 2, extra);
	auxspi_read_data (offset1, &buf4, 1, 2, extra);
	auxspi_write_data(offset0, &buf1, 1, 2, extra);

	if (buf4 != buf2) return 0x0d; // 8KB (64kbit)
	else return 0x10; // 64KB (512kbit)
}

uint8_t auxspi_save_type(enum auxspi_extra extra) {
	uint32_t jedec = auxspi_save_jedec_id(extra); // 9f
	int8_t sr = auxspi_save_status_register(extra); // 05

	if ((sr & 0xfd) == 0xf0 && (jedec == 0x00ffffff)) return 1;
	if ((sr & 0xfd) == 0x00 && (jedec == 0x00ffffff)) return 2;
	if ((sr & 0xfd) == 0x00 && (jedec != 0x00ffffff)) return 3;

	return 0;
}

uint32_t auxspi_save_size(enum auxspi_extra extra) {
	return 1 << auxspi_save_size_log_2(extra);
}

uint8_t auxspi_save_size_log_2(enum auxspi_extra extra) {
	switch (auxspi_save_type(extra)) {
	case 1:
		return 0x09; // 512 bytes
	case 2:
		return type2_size(extra);
	case 3:
		return jedec_table(auxspi_save_jedec_id(extra));
	}

	return 0;
}

uint32_t auxspi_save_jedec_id(enum auxspi_extra extra) {
	uint32_t id = 0;
	if (extra) auxspi_disable_extra(extra);

	auxspi_open(0);
	auxspi_write(0x9f);
	id |= auxspi_read() << 16;
	id |= auxspi_read() << 8;
	id |= auxspi_read();
	auxspi_close();

	return id;
}

uint8_t auxspi_save_status_register(enum auxspi_extra extra) {
	uint8_t sr = 0;
	if (extra) auxspi_disable_extra(extra);

	auxspi_open(0);
	auxspi_write(0x05);
	sr = auxspi_read();
	auxspi_close();
	return sr;
}

void auxspi_read_data(uint32_t addr, void* buf, uint32_t cnt, uint8_t type, enum auxspi_extra extra) {
	if (type == 0) type = auxspi_save_type(extra);
	if (type == 0) return;

	if (extra) auxspi_disable_extra(extra);

	auxspi_open(0);
	auxspi_write(0x03 | ((type == 1) ? addr>>8<<3 : 0));

	if (type == 3) auxspi_write((addr >> 16) & 0xFF);
	if (type >= 2) auxspi_write((addr >>  8) & 0xFF);
	auxspi_write(addr & 0xFF);

	for (; cnt; ++buf, --cnt)
		*(uint8_t*)buf = auxspi_read();

	auxspi_close();
}

void auxspi_disable_extra(enum auxspi_extra extra) {
	if (extra == AUXSPI_INFRARED)
		auxspi_disable_infrared();
}

void auxspi_disable_infrared(void) {
	auxspi_open(0);
	swiDelay(1200);
	auxspi_open(2);
	auxspi_write(0);
	swiDelay(1200);
}

enum auxspi_extra auxspi_has_extra(void) {
	sysSetBusOwners(true, true);

	// Trying to read the save size in IR mode will fail on non-IR devices.
	// If we have success, it is an IR device.
	uint8_t size2 = auxspi_save_size_log_2(AUXSPI_INFRARED);
	if (size2 > 0)
		return AUXSPI_INFRARED;

	// It is not an IR game, so maybe it is a regular game.
	uint8_t size1 = auxspi_save_size_log_2(AUXSPI_DEFAULT);
	if (size1 > 0)
		return AUXSPI_DEFAULT;

	return AUXSPI_FLASH_CARD;
}

void auxspi_write_data(uint32_t addr, const void* buf, uint32_t cnt, uint8_t type, enum auxspi_extra extra) {
	if (type == 0) type = auxspi_save_type(extra);
	if (type == 0) return;

	uint32_t addr_end = addr + cnt;
	unsigned int maxblocks = 32;
	if (type == 1) maxblocks = 16;
	if (type == 2) maxblocks = 32;
	if (type == 3) maxblocks = 256;

	// we can only write a finite amount of data at once, so we need a separate loop
	//  for multiple passes.
	while (addr < addr_end) {
		if (extra)
			auxspi_disable_extra(extra);

		auxspi_open(0);
		// set WEL (Write Enable Latch)
		auxspi_write(0x06);
		auxspi_close_hold_chipsel();

		if (extra) auxspi_disable_extra(extra);

		auxspi_open(0);
		// send initial "write" command
		if (type == 1) {
			auxspi_write(0x02 | (addr & BIT(8)) >> (8-3));
			auxspi_write(addr & 0xFF);
		}
		else if (type == 2) {
			auxspi_write(0x02);
			auxspi_write((addr >> 8) & 0xff);
			auxspi_write(addr & 0xFF);
		}
		else if (type == 3) {
			auxspi_write(0x02);
			auxspi_write((addr >> 16) & 0xff);
			auxspi_write((addr >>  8) & 0xff);
			auxspi_write(addr & 0xFF);
		}

		for (uint32_t i = 0; addr < addr_end && i < maxblocks; ++i, ++addr, ++buf) {
			auxspi_write(*(const uint8_t*)buf);
		}

		auxspi_close_hold_chipsel();

		// wait programming to finish
		if (extra) auxspi_disable_extra(extra);

		auxspi_open(0);
		auxspi_write(5);
		auxspi_wait_wip();
		auxspi_wait_busy();
		auxspi_close();
	}
}

