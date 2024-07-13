/*
 * savegame_manager: a tool to backup and restore savegames from Nintendo
 *  DS cartridges. Nintendo DS and all derivative names are trademarks
 *  by Nintendo. EZFlash 3-in-1 is a trademark by EZFlash.
 *
 * auxspi.h: Header for auxspi.cpp
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
/*
  This is a thin reimplementation of the AUXSPI protocol at low levels.
  It is used to implement various experimental procedures to test accessing the HG/SS save chip. */

#ifndef SPI_BUS_H
#define SPI_BUS_H

#include <stdint.h>
#include <stdbool.h>

// This is a handy typedef for nonstandard SPI buses, i.e. games with some
//  extra hardware on the cartridge. The following values mean:
// AUXSPI_DEFAULT: A regular game with no exotic hardware.
// AUXSPI_INFRARED: A game with an infrared transceiver.
//  Games known to use this hardware:
//  - Personal Trainer: Walking (aka Laufrhytmus DS, Walk With Me, ...)
//  - Pokemon HeartGold/SoulSilver/Black/White
// AUXSPI_BBDX: A game with what seems to be an extra protection against reading
//  out the chip. Exclusively found on Band Brothers DX.
// AUXSPI_BLUETOOTH: A game with a Bluetooth transceiver. The only game using this
//  hardware is Pokemon Typing DS.
//
// NOTE: This library does *not* support BBDX (I do have the game, but did not find the
//  time to reverse engineer this; besides, a separate homebrew for this game already exists),
//  and also *not* BLUETOOTH (the game is Japan-only, and I am from Europe. Plus I can't
//  read Japanese. And it is unlikely that this game will ever make it here.)
//
enum auxspi_extra {
	AUXSPI_DEFAULT,
	AUXSPI_INFRARED,
	AUXSPI_BBDX,
	AUXSPI_BLUETOOTH,
	AUXSPI_FLASH_CARD = 999
};

// These functions reimplement relevant parts of "card.cpp", in a way that is easier to modify.
uint8_t  auxspi_save_type(enum auxspi_extra extra);
uint32_t auxspi_save_size(enum auxspi_extra extra);
uint8_t  auxspi_save_size_log_2(enum auxspi_extra extra);
uint32_t auxspi_save_jedec_id(enum auxspi_extra extra);
uint8_t  auxspi_save_status_register(enum auxspi_extra extra);

void auxspi_read_data (uint32_t addr,       void* buf, uint32_t size,
		uint8_t type, enum auxspi_extra extra);
void auxspi_write_data(uint32_t addr, const void* buf, uint32_t size,
		uint8_t type, enum auxspi_extra extra);

// These functions are used to identify exotic hardware.
enum auxspi_extra auxspi_has_extra(void);

void auxspi_disable_extra(enum auxspi_extra extra);
void auxspi_disable_infrared(void);

#endif
