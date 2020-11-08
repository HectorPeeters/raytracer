#pragma once

#include <limits>
#include <stdlib.h>

#include "log.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long i64;

typedef float f32;
typedef double f64;

#define EPSILON 0.00001f
#define F32_MAX std::numeric_limits<f32>::max()
#define U64_MAX 18446744073709551615

#define APPROX_EQ(X, Y) abs(X - Y) < EPSILON

#define ALLOC(T) (T *)malloc(sizeof(T))
#define ALLOC_SIZED(T, S) (T *)malloc(S * sizeof(T))

#define FREE(x) free(x)

#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    LERR("Assertion failed!");

#define UNREACHABLE()                                                          \
  {                                                                            \
    LERR("Unreachable code");                                                  \
    exit(1);                                                                   \
  }

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
