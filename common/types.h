#ifndef EQC_COMMON_TYPES_H
#define EQC_COMMON_TYPES_H

#include <stdint.h>
typedef uint8_t uchar;
typedef uint8_t byte;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

#define safe_delete(x) if(x) { delete x; x = nullptr; }
#define safe_delete_array(x) if(x) { delete[] x; x = nullptr; }

#endif
