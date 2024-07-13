
# Pokewalker ROM dumper

Dump both Pokéwalker ROMs using your DSi and HGSS/BW/B2W2 cartridge.

## Download

[Linky](https://pcy.be/tmp/miscbin/auxspi-ir.nds)

## Usage

Launch the DSi homebrew file using your favourite exploit/homebrew menu.
Preferably, only launch it *after* inserting the IR-capable cart. If you insert
a non-IR-capable cart (eg. a flashcart) and launch it, it'll freeze.

Press `A` to do a test communication thing (it shows the trainer name stored on
the Walker), `X` to dump the EEPROM, `Y` to restore it, `B` to dump the
internal flash ROM.

ROMs are dumped to the SD card, so you need a DSi or 3DS/2DS, sorry.

Some extra features: `L` can be used to run your own code on the walker (place
code in `/pwcode.bin` on your SD card), and `R` dumps the entire ROM and RAM
from the IR MCU that's inside your game cartridge.

***NOTE***: the EEPROM restore functionality is UNTESTED! This MAY CAUSE DATA
LOSS OR MAYBE EVEN A BRICK! **YOU HAVE BEEN WARNED!**

## Compatiblity

Tested with HGSS, BW and B2W2, seems to work with all of these. Unknown whether
it works with other cartridges with an IR transceiver, but it probably does.

Only tested on a DSi running in DSi mode. Others tell me it works on a 3DS/2DS in
DSi backwards-compat mode as. Doesn't work on a regular DS due to the
beforementioned SD card problem.

You *could* port it to a regular DS by fixing the cart booting logic (it's
currently untested), and adding extra logic to keep the dumps in RAM while an
IR cart is inserted, and only write them out when that cart is swapped out to
a flashcart.

## Compilation

Compile with devkitARM. needs libnds, libfat and libfilesystem.

## Running your custom code on the Pokéwalker

Some example code, as well as "header" files for MMIO regs and ROM subroutines,
are available in the `pw/` folder. You need GNU Binutils configured for
`h8300-hitachi-elf`. The `Makefile` in the folder will turn your assembly
code into a neat binary the NDS homebrew ROM will happily send to your walker,
as long as it's 125 bytes or less in size.

## How does it work

For information on how to do IR communications from the NDS side, see [this
melonDS BBS post](http://melonds.kuribo64.net/board/thread.php?pid=2762#2762)
(own work):

> IR cartridges seem to work as follows, but I'd like to have someone else to
> verify this (seems to work with HGSS, BW and B2W2 carts, idk about others):
>
> Everything automatically happens at 115200 baud, 8n1.
>
> There seem to be three main SPI commands that are sent to what normally would
> be the savegame SPI bus, there's a fourth command to perform actual savegame
> operations. All transfers happen at 1 MHz (serial AUXSPI mode) unless indicated
> otherwise.
>
> The cartridge needs to be powered on, but nothing more besides this. No header
> reading or KEY1/KEY2 init, and so on. (I rebooted the cart with SCFG_MC and
> started doing SPI commands immediately afterwards, seems to work fine).
>
> This seems to be relevant for pretty much all NTR-031 carts, so Pokémon HGSS,
> BW, B2W2, "Walk With Me" and similar games, ...
>
> The commands:
>
> * 0x00: savegame escape byte: as long as chip select is held, the bytes that
>   follow will be treated like a regular savegame transfer. These can also happen
>   at any clock speed, but the 0x00 byte itself needs to be transferred at 1 MHz.
>   (This bit was already known.)
> * 0x01: receive data from IR: one command byte (0x01) is written, after which
>   data bytes are read by the DS. The first byte read indicates the amount of
>   bytes that will follow. It doesn't seem to be able to receive more than 255
>   bytes afaics. Bytes written to perform the reads are unused as far as I know,
>   but usually set to 0 (HGSS does this, at least).
>   * When there are zero bytes to read, you still have to deselect the SPI chip, or
>     the next transfer will fail. Disable the 'chip select hold' bit in AUXSPICNT
>     and send a zero byte.
> * 0x02: send data over IR: this one has no length prefix, chip select is used to
>   determine when the transfer ends, as usual.
> * 0x03: write byte to in-cart IR MCU RAM: send high addr byte and low addr byte,
>   then send a data byte. Writes the data byte to the specified address in the
>   in-cartridge IR MCU. Discovered by nocash.
> * 0x04: read byte from in-cart IR MCU RAM: send high addr byte and low addr byte,
>   then read a data byte. Can be used to dump the ROM inside the in-cart IR MCU.
>   Discovered by nocash.
> * 0x05: write word to in-cart IR MCU RAM: send high addr byte and low addr byte,
>   then send two data bytes. Discovered by nocash.
> * 0x06: read word from in-cart IR MCU RAM: send high addr byte and low addr byte,
>   then read two data bytes. Discovered by nocash.
> * 0x07: mystery command, purpose unclear. Discovered by nocash.
> * 0x08: not too sure about this, but probably a status thing. A command byte
>   (0x08) is sent, and a status byte(?) is received from the cart. HGSS seems to
>   always send two of these one after another, carts seem to return 0x00 on the
>   first one and 0xaa for the second, unless other IR devices are sending
>   actively, then both bytes are 0xaa. Allegedly, "Walk With Me" and similar games
>   don't have this command.
>
> HGSS, while trying to connect to a Pokéwalker, seems to first do a cmd 0x01,
> which returns 0 bytes, then 0x08 twice, after which it repeatedly issues other
> 0x01 commands until the return data of one of these indicates a Pokéwalker
> presence (the Pokéwalker sends out a fixed byte value as 'beacon' thing, the
> game will receive a 1-byte packet containing that beacon). 0x08 is never used
> again after being used twice in the beginning as far as I can see (but I might
> be wrong).
>
> Allegedly, the chip in carts responsible for IR is another H8/38606F (or
> 38602F?) (connected to the SPI bus on one side, and to some IR leds or so on
> the other).
>
> [UPDATE: 2021-03-01: added info on cmd 0x03..0x07, and non-Pokémon games. info
> from nocash, not me.]

Everything else (exploit payload etc.) came from [Dmitry's absolutely great
writeup](http://dmitry.gr/?r=05.Projects&proj=28.%20pokewalker#_TOC_af123b35f7bb7a64f7b746e581c6d8af).

AUXSPI, IR and Pokéwalker functionality is all wrapped into neat(`DISPUTED`)
packages you can use.

## License

GPLv3, because parts of the `auxspi.c` code come from a GPLv2 repo, and
Dmitry's code is GPLv3, which I also consulted a bit.

## Greets

Dmitry, mamba2410, nocash, Team Pokeme, and the melonDS dev team.

