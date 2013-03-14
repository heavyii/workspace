/*
 * crc16.c
 *
 *  Created on: Jan 9, 2013
 *      Author: heavey
 */

#include "crc16.h"

uint16_t crc16_byte(uint16_t crc, unsigned char b) {
	unsigned char i;

	crc = crc ^ b << 8;
	i = 8;
	do
		if (crc & 0x8000)
			crc = crc << 1 ^ 0x1021;
		else
			crc = crc << 1;
	while (--i);

	return crc;
}

uint16_t crc16(unsigned char *p, int len){
	uint16_t crc;
	crc = 0;

	while(len--)
		crc = crc16_byte(crc, *p++);

	return crc;
}
