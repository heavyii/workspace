/*
 * crc16.h
 *
 *  Created on: Jan 9, 2013
 *      Author: heavey
 */

#ifndef CRC16_H_
#define CRC16_H_

#include <stdint.h>

uint16_t crc16_byte(uint16_t crc, unsigned char b);
uint16_t crc16(unsigned char *p, int len);
#endif /* CRC16_H_ */
