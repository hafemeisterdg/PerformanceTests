#pragma once

#if !defined(__cplusplus)
#include <stdbool.h>
#endif

#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t  i8;

typedef double f64;
typedef float  f32;

#define internal static
#define global   static
#define local    static

#define Kilobyte(x)(x * 1024ULL)
#define Megabyte(x)(Kilobyte(x) * 1024ULL)
#define Gigabyte(x)(Megabyte(x) * 1024ULL)