
#ifndef IR_H_
#define IR_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "auxspi.h"

bool auxspi_init_ir(bool wait_on_empty_slot, enum auxspi_extra* extra, uint8_t* savetype);
uint8_t auxspi_xfer_ir/*_base*/(uint8_t val, bool hold/*, bool reinit*/);
/*#define auxspi_xfer(val, hold, ...) auxspi_xfer_base(val, hold, (0, ##__VA_ARGS__))*/

enum ir_cmdtype {
	ir_cmd_beacon = 0xfc,
	ir_cmd_syn    = 0xfa
};
enum ir_extra {
	ir_extra_mosi = 0x01,
	ir_extra_miso = 0x02,

	ir_extra_addrhi = 0x80
};

// receive from IR
size_t ir_cmd1(uint8_t* rxbuf /* either at least size 256, or NULL! */);
// send over IR
void ir_cmd2(size_t size, const uint8_t* txbuf);
// read byte at address from in-cartridge CPU
uint8_t ir_cmd4(uint16_t addr);
// TODO: cmd3: write byte to in-cart CPU
//       cmd5,6: write/read word to/from in-cart CPU
//       cmd7: "?"
uint8_t ir_cmd8(void);

inline static uint16_t ir_stat(void) {
	uint8_t lo = ir_cmd8(),
			hi = ir_cmd8();

	return lo | ((uint16_t)hi << 8);
}

void ir_init(void);

#define IR_XOR_KEY 0xaa

uint16_t ir_calc_crc(uint8_t type, uint8_t extra, uint32_t sessid,
		const uint8_t* payload, size_t payload_len);

void ir_send_syn(uint32_t  sessid_gm);
bool ir_recv_ack(uint32_t* sessid_pw);

#endif

