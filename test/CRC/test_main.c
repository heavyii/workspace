#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "crc32.h"

static void test_crc32(void) {
	int i;
	struct packet_crc32_t {
		unsigned char data[1024];
		int len;
		unsigned int crc;
	};

	struct packet_crc32_t pkt;
	memset(&pkt, 0xa3, sizeof(pkt));
	pkt.len = 1024;

	//calculate crc32 value
	pkt.crc = cyg_crc32(pkt.data, pkt.len);

	printf("crc is 0x%x\n", pkt.crc);
}

static void test_crc16(void) {

	struct packet_crc16_t {
		unsigned char data[1024];
		int len;
		unsigned short crc;
	};

	struct packet_crc16_t pkt;

	memset(pkt.data, 0x2f, sizeof(pkt.data));
	pkt.len = sizeof(pkt.data);

	//calculate crc16 value
	pkt.crc = crc16(pkt.data, pkt.len);

	printf("crc16 is 0x%x\n", pkt.crc);

	/*
	 * test again
	 */
	int i;
	unsigned short crc = 0;
	unsigned char *p = pkt.data;
	for (i = 0; i < pkt.len; i++)
		crc = crc16_byte(crc, *p++);

	printf("crc is 0x%x\n", crc);
}

/*
 * example
 * This demo shows you how to add 4 bytes to change CRC32 value to
 * whatever you want. And how to reverse CRC32 value by dropping
 * bytes from target CRC32 value.
 */
static void test_crc_reverse(void) {
	int i;
	uint8_t num[4] = { 0, 0, 0, 0 };
	unsigned int crc_dst = 0;
	unsigned int crc_src = 0;

	printf("crc32: reverse 4 bytes\n");
	printf("crc32: enter 2 CRC value: src dst\n");
	scanf("%08x %08x", &crc_src, &crc_dst);

	cyg_crc32_change(crc_dst, crc_src, num);

	printf("Add those 4 bytes: ( ");
	for (i = 0; i < 4; i++) {
		printf("%02hhx ", num[i]);
	}
	printf(") to change CRC %08x to %08x\n", crc_src, crc_dst);

	printf("change  crc: %08x ==> %08x\n", crc_src,
			cyg_crc32_accumulate(crc_src, num, 4));

	printf("reserve crc: %08x ==> %08x\n", crc_dst,
			cyg_crc32_reserve(crc_dst, num, 4));

	return;
}

int main(int argc, char **argv) {

	test_crc32();
	test_crc16();

	test_crc_reverse();
	return 0;
}

