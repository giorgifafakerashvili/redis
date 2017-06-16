#ifdef _CRC64_H_
#define _CRC64_H_

#include <stdint.h>

uint64_t crc64(uint64_t crc, const unsigned char* s, uint64_t l);

#ifdef REDIS_TEST
int crc64Test(int argc, char* argv[]);
#endif



#endif // _CRC64_H_
