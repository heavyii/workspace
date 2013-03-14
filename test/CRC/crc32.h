//==========================================================================
//
//      crc.h
//
//      Interface for the CRC algorithms.
//==========================================================================

#ifndef __CRC32_H__
#define __CRC32_H__

#include <stdint.h>
// Gary S. Brown's 32 bit CRC

uint32_t cyg_crc32(unsigned char *s, int len);

// Gary S. Brown's 32 bit CRC, but accumulate the result from a
// previous CRC calculation

uint32_t cyg_crc32_accumulate(uint32_t crc, unsigned char *s, int len);

// Ethernet FCS Algorithm

uint32_t cyg_ether_crc32(unsigned char *s, int len);

// Ethernet FCS algorithm, but accumulate the result from a previous
// CRC calculation.

uint32_t cyg_ether_crc32_accumulate(uint32_t crc, unsigned char *s,
		int len);

/**
 * add 4 bytes num[4] to change crc32 value from crc_src to crc_dst
 * @return: 0 on success, -1 on error.
 */
int cyg_crc32_change(uint32_t crc_dst, uint32_t crc_src, uint8_t num[4]);

/**
 * cyg_crc32_reserve - reserve CRC32 value by dropping data[len]
 * @return: return the CRC value before data[len]
 */
uint32_t cyg_crc32_reserve(uint32_t crc, void *data, int len);

#endif // __CRC32_H__
