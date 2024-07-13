
#ifndef PW_H_
#define PW_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define PW_XOR_KEY   0xaa
#define PW_XOR_KEY16 0xaaaa
#define PW_XOR_KEY32 0xaaaaaaaa

enum pw_cmdtype {
	pw_cmd_beacon = 0xfc,
	pw_cmd_syn    = 0xfa,
	pw_cmd_ack    = 0xf8,
	pw_cmd_rst    = 0xf4,

	pw_cmd_ping   = 0x24,
	pw_cmd_pong   = 0x26,

	pw_sploit_cmd_dump_res = 0x3c,

	pw_cmd_kill   = 0x56,
	pw_cmd_close  = 0x66,
	pw_cmd_cloack = 0x68,

	pw_cmd_geninf_req = 0x20,
	pw_cmd_geninf_res = 0x22,

	pw_cmd_eepwrite_align_req = 0x02,
	pw_cmd_eepwrite_res = 0x04,
	pw_cmd_eepwrite_req = 0x0a,

	pw_cmd_memwrite_req = 0x06,
	pw_cmd_memwrite_res = 0x06,

	pw_cmd_eepread_req = 0x0c,
	pw_cmd_eepread_res = 0x0e
};
enum pw_extra {
	pw_extra_g2w = 0x01,
	pw_extra_w2g = 0x02,

	pw_extra_addrhi = 0x80
};

bool pw_scan(void);

uint16_t pw_calc_crc(uint8_t type, uint8_t extra, uint32_t sessid,
		const uint8_t* payload, size_t payload_len);

void pw_send_syn(uint32_t  sessid_gm); // fa
bool pw_recv_ack(uint32_t* sessid_pw); // f8
void pw_conn_rst(uint32_t sessid); // 0xf4


typedef void (*pw_wait_f)(size_t i);
extern size_t pw_poll_tries;
extern pw_wait_f pw_poll_wait;
void pw_poll_wait_default(size_t i);


bool pw_do_synack(uint32_t* sessid_glob);

bool pw_pingpong(uint32_t sessid); // 0x24/0x26

void pw_conn_kill(uint32_t sessid); // 0x56
bool pw_conn_end (uint32_t sessid); // 0x66/0x68


// cmd 0x20/0x22
__attribute__((__packed__)) struct pw_geninfo { // aka "IDENTITY DATA"
	uint32_t _unk0[2];
	uint16_t _unka[2];
	uint16_t trainer_tid;
	uint16_t trainer_sid;
	uint8_t  uuid[0x28];
	uint8_t  event_bitfields[0x10];
	uint16_t trainer_name[8];
	uint8_t  _unk1[3];
	uint8_t  flags;
	uint8_t  proto_ver_maj;
	uint8_t  _unk2;
	uint8_t  proto_ver_min;
	uint8_t  _unk3;
	uint32_t last_sync_time;
	uint32_t step_count;
};
bool pw_get_geninfo(uint32_t sessid, struct pw_geninfo* geninf);


bool pw_write_mem(uint32_t sessid, uint16_t addr, size_t size, const uint8_t* data); // 0x06
bool pw_read_eeprom(uint32_t sessid, uint16_t addr, size_t size, uint8_t* dest);
bool pw_write_eeprom(uint32_t sessid, uint16_t addr, size_t size, const uint8_t* src);

// NOTE: does ASCII only!
char pw_charconv_w2a(uint16_t wch);
uint16_t pw_charconv_a2w(char a);

ptrdiff_t pw_sploit_recv_dump_seg(uint32_t sessid, uint8_t dest[0x180]);

void wwm_syn(unsigned address, unsigned length);
bool wwm_ack(uint8_t *buffer);

#endif

