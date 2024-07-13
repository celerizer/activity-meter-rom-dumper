
#include <nds.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "ir.h"

#include "pw.h"

__attribute__((__aligned__(4))) static uint8_t rxbuf[256];
__attribute__((__aligned__(4))) static uint8_t txbuf[256];

inline static uint16_t to_le16(uint16_t v) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return v;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return ((v>>8) & 0xff) | ((v&0xff) << 8);
#else
#error "Unuspported endianness."
#endif
}
inline static uint16_t to_be16(uint16_t v) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return ((v>>8) & 0xff) | ((v&0xff) << 8);
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return v;
#else
#error "Unuspported endianness."
#endif
}
inline static uint32_t to_le32(uint32_t v) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return v;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return ((v>>24) & 0xff) | ((v&0xff) << 24)
		| ((v>>8) & 0xff00) | ((v&0xff00) << 8);;
#else
#error "Unuspported endianness."
#endif
}
inline static uint32_t to_be32(uint32_t v) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return ((v>>24) & 0xff) | ((v&0xff) << 24)
		| ((v>>8) & 0xff00) | ((v&0xff00) << 8);;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return v;
#else
#error "Unuspported endianness."
#endif
}

size_t pw_poll_tries = 0x10;
pw_wait_f pw_poll_wait = pw_poll_wait_default;

void pw_poll_wait_default(size_t i) {
	(void)i;
	swiWaitForVBlank();
}

bool pw_scan(void) {
	size_t len = ir_cmd1(rxbuf);

	return len == 1 && (rxbuf[0]^PW_XOR_KEY) == pw_cmd_beacon;
}

uint16_t pw_calc_crc(uint8_t type, uint8_t extra, uint32_t sess,
		const uint8_t* payload, size_t payload_len) {
	uint32_t crc = 0; // 0x0002; // fixed start value

	crc += (uint32_t)type  << 8;
	crc += (uint32_t)extra << 0;

	// crc += ( sess        & 0xff) << 8;
	// crc += ((sess >>  8) & 0xff) << 0;
	// crc += ((sess >> 16) & 0xff) << 8;
	// crc += ((sess >> 24) & 0xff) << 0;

	for (size_t i = 0; i < payload_len; ++i)
		crc += payload[i] << ((i & 1) ? 0 : 8);

	while (crc >> 16)
		crc = (crc & 0xffff) + (crc >> 16);

	return crc;
}

static bool verbose_xceive = true;

static void pw_send(enum pw_cmdtype cmd, enum pw_extra extra, uint32_t sessid,
		size_t size, uint8_t* data) {
	if (size > 255) return;

	uint16_t crc = pw_calc_crc(cmd, extra, sessid, data, size);

	//if (verbose_xceive) {
		iprintf("sending cmd%02x ex%02x "/*"crc=%04x sess=%08lx "*/"plsize=%zu\n",
				cmd, extra, /*crc, sessid,*/ size);
	//}
	txbuf[0] = cmd ^ PW_XOR_KEY;
	txbuf[1] = extra ^ PW_XOR_KEY;
	((uint16_t*)txbuf)[1] = crc ^ PW_XOR_KEY16;
	// ((uint32_t*)txbuf)[1] = sessid ^ PW_XOR_KEY32;
	for (size_t i = 0; i < size; ++i) txbuf[i+4] = data[i] ^ PW_XOR_KEY;

	ir_cmd2(4+size, txbuf);
}
static ptrdiff_t pw_recv(enum pw_cmdtype cmd, uint32_t sessid, bool check_sessid) {
	size_t size;

	for (size_t iii = 0; iii < pw_poll_tries; ++iii) {
		size = ir_cmd1(rxbuf);
		if (verbose_xceive) {
			if (size) {
				iprintf("recv %zu want cmd%02x", size, cmd);
				//if (check_sessid) iprintf(" (want sessid %08lx)", sessid);
				iprintf("\n");
			}
		}

		if (size >= 4) {
			((uint32_t*)rxbuf)[0] ^= PW_XOR_KEY32; // OK with endianness
			// ((uint32_t*)rxbuf)[1] ^= PW_XOR_KEY32;
			for (size_t i = 0; i < size-4; i++) rxbuf[i+4] ^= PW_XOR_KEY;

			// uint32_t sessid_pkt = to_le32(((uint32_t*)rxbuf)[1]);
			// uint16_t crc_clc = pw_calc_crc(rxbuf[0], rxbuf[1], sessid_pkt, &rxbuf[8], size-8);
			// uint16_t crc_pkt = to_le16(((uint16_t*)rxbuf)[1]);

			if (verbose_xceive)
				iprintf("size %zu "/*"sessid=%08lx"*/" ""got cmd%02x ex%02x\n",
						size,/*sessid_pkt,*/ rxbuf[0], rxbuf[1]);

			// if (rxbuf[0] == cmd && (sessid_pkt == sessid || !check_sessid))
				// if (crc_clc == crc_pkt) 
        return size;
		}
		//else if (verbose_xceive) iprintf("\n");


		if (pw_poll_wait) pw_poll_wait(iii);
	}

	return -1;
}

void pw_send_syn(uint32_t  sessid_gm) {
	pw_send(pw_cmd_syn, pw_extra_g2w, sessid_gm, 0, NULL);
}
bool pw_recv_ack(uint32_t* sessid_pw) {
	ptrdiff_t sz = pw_recv(pw_cmd_ack, 0, false);
	if (sz < 0)
		return false;

	if (rxbuf[1] == pw_extra_w2g && sz == 8) {
		if (sessid_pw) *sessid_pw = to_le32(((uint32_t*)rxbuf)[1]);

		return true;
	}

	return false;
}
void pw_conn_rst(uint32_t sessid) {
	pw_send(pw_cmd_rst, pw_extra_g2w, sessid, 0, NULL);
}


bool pw_do_synack(uint32_t* sessid_glob) {
	uint32_t sessid_pw = 0;
	uint32_t sessid_gm = ((uint32_t)REG_VCOUNT << 16) // good enough
		| (((size_t)&sessid_pw & 0xffff) ^ TIMER0_DATA ^ TIMER3_DATA);

	pw_send_syn(sessid_gm);
	if (pw_recv_ack(&sessid_pw) && rxbuf[1]) {
		if (sessid_glob) *sessid_glob = sessid_pw ^ sessid_gm;

		return true;
	}

	return false;
}

bool pw_pingpong(uint32_t sessid) {
	pw_send(pw_cmd_ping, pw_extra_g2w, sessid, 0, NULL);

	ptrdiff_t sz = pw_recv(pw_cmd_pong, sessid, true);

	return sz == 8 && rxbuf[1] == pw_extra_w2g;
}

void pw_conn_kill(uint32_t sessid) {
	pw_send(pw_cmd_kill, pw_extra_g2w, sessid, 0, NULL);
}
bool pw_conn_end (uint32_t sessid) {
	pw_send(pw_cmd_close, pw_extra_g2w, sessid, 0, NULL);

	return pw_recv(pw_cmd_cloack, sessid, true) == 8 && rxbuf[1] == pw_extra_w2g;
}


bool pw_get_geninfo(uint32_t sessid, struct pw_geninfo* gi) {
	if (!gi) return false;

	pw_send(pw_cmd_geninf_req, pw_extra_g2w, sessid, 0, NULL);

	if (pw_recv(pw_cmd_geninf_res, sessid, true) != 8+0x68
			|| rxbuf[1] != pw_extra_w2g)
		return false;

	*gi = *(struct pw_geninfo*)&rxbuf[8];

	for (size_t i = 0; i < 2; ++i)
		gi->_unk0[i] = to_le32(gi->_unk0[i]);
	for (size_t i = 0; i < 2; ++i)
		gi->_unka[i] = to_le16(gi->_unka[i]);
	gi->trainer_tid    = to_le16(gi->trainer_tid   );
	gi->trainer_sid    = to_le16(gi->trainer_sid   );
	for (size_t i = 0; i < 8; ++i)
		gi->trainer_name[i] = to_le16(gi->trainer_name[i]);
	gi->last_sync_time = to_be32(gi->last_sync_time);
	gi->step_count     = to_be32(gi->step_count    );

	return true;
}


bool pw_write_mem(uint32_t sessid, uint16_t addr, size_t size, const uint8_t* data) {
	if (size > 254 || !data) return false;

	//verbose_xceive = true;

	uint8_t pl[size+1];
	pl[0] = addr & 0xff;
	for (size_t i = 0; i < size; ++i) pl[i+1] = data[i];
	pw_send(pw_cmd_memwrite_req, (addr >> 8) & 0xff, sessid, size+1, pl);

	bool r = pw_recv(pw_cmd_memwrite_res, sessid, true) == 8;
	//verbose_xceive = false;
	return r;
}
bool pw_read_eeprom(uint32_t sessid, uint16_t addr, size_t size, uint8_t* dest) {
	if (size > 255 || !dest) return false;

	uint8_t pl[3];
	pl[0] = (addr>>8);
	pl[1] = addr&0xff;
	pl[2] = size;

	pw_send(pw_cmd_eepread_req, addr >> 8, sessid, 3, pl);

	if (pw_recv(pw_cmd_eepread_res, sessid, true) != 8+size || rxbuf[1] != pw_extra_w2g)
		return false;

	for (size_t i = 0; i < size; ++i)
		dest[i] = rxbuf[i+8];

	return true;
}
bool pw_write_eeprom(uint32_t sessid, uint16_t addr, size_t size, const uint8_t* src) {
	if (size > 255 || !src || size >= 0x80) return false;

	uint8_t pl[0x80];
	pl[0] = addr&0xff;
	memcpy(&pl[1], src, size);

	pw_send(pw_cmd_eepwrite_req, (uint8_t)(addr >> 8), sessid, size+1, src);

	if (pw_recv(pw_cmd_eepwrite_res, sessid, true) != 8 || rxbuf[1] != pw_extra_w2g)
		return false;

	return true;
}


char pw_charconv_w2a(uint16_t wch) {
	if (wch == 0 || ~(uint16_t)wch == 0) return 0;

	if (wch >= 0x121 && wch <= 0x12a) return (wch - 0x121) + '0';
	if (wch >= 0x12b && wch <= 0x144) return (wch - 0x12b) + 'A';
	if (wch >= 0x145 && wch <= 0x15e) return (wch - 0x145) + 'a';
	if (wch == 0x1a8) return '$';
	if (wch == 0x1ab) return '!';
	if (wch == 0x1ac) return '?';
	if (wch == 0x1ad) return ',';
	if (wch == 0x1ae) return '.';
	if (wch == 0x1b1) return '/';
	if (wch == 0x1b9 || wch == 0x1ba) return '(' + (wch - 0x1b9);
	if (wch == 0x1bd) return '+';
	if (wch == 0x1be) return '-';
	if (wch == 0x1bf) return '*';
	if (wch == 0x1c0) return '#';
	if (wch == 0x1c1) return '=';
	if (wch == 0x1c2) return '&';
	if (wch == 0x1c3) return '~';
	if (wch == 0x1c4) return ':';
	if (wch == 0x1c5) return ';';
	if (wch == 0x1d0) return '@';
	if (wch == 0x1d2) return '%';
	if (wch == 0x1de) return ' ';
	if (wch == 0x1e9) return '_';

	return 0xff;
}
uint16_t pw_charconv_a2w(char a) {
	if (!a || (a & 0x80)) return 0xffff;

	if (a >= '0' && a <= '9') return (uint16_t)(a - '0') + 0x121;
	if (a >= 'A' && a <= 'Z') return (uint16_t)(a - 'A') + 0x12b;
	if (a >= 'a' && a <= 'z') return (uint16_t)(a - 'a') + 0x145;
	if (a == '$') return 0x1a8;
	if (a == '!') return 0x1ab;
	if (a == '?') return 0x1ac;
	if (a == ',') return 0x1ad;
	if (a == '.') return 0x1ae;
	if (a == '/') return 0x1b1;
	if (a == '(' || a == ')') return (uint16_t)(a - '(') + 0x1b9;
	if (a == '+') return 0x1bd;
	if (a == '-') return 0x1be;
	if (a == '*') return 0x1bf;
	if (a == '#') return 0x1c0;
	if (a == '=') return 0x1c1;
	if (a == '&') return 0x1c2;
	if (a == '~') return 0x1c3;
	if (a == ':') return 0x1c4;
	if (a == ';') return 0x1c5;
	if (a == '@') return 0x1d0;
	if (a == '%') return 0x1d2;
	if (a == ' ') return 0x1de;
	if (a == '_') return 0x1e9;

	return 0xffff;
}

ptrdiff_t pw_sploit_recv_dump_seg(uint32_t sessid, uint8_t dest[0x80]) {
	verbose_xceive = true;

	ptrdiff_t sz = pw_recv(pw_sploit_cmd_dump_res, sessid, true);
	if (sz < 8) {
		verbose_xceive = false;
		return -1;
	}
	sz -= 8;

	for (size_t i = 0; i < sz; ++i)
		dest[i] = rxbuf[i+8];

	verbose_xceive = false;
	return sz;
}

void wwm_syn(unsigned address, unsigned length)
{
  uint8_t data[3] = { (address >> 8) & 0xFF, address & 0xFF, length };
  pw_send(0x0A, 0x00, 0, sizeof(data), data);
}

bool wwm_ack(uint8_t *buffer)
{
  ptrdiff_t sz = pw_recv(0x0A, 0, 0);

  if (sz < 0)
		return false;
  else
  {
    iprintf("Received %u bytes: \n", sz);
    for (size_t i = 0; i < sz-4; i++)
		  buffer[i] = rxbuf[i+4];
  }

  return true;
}
