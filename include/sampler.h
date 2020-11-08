#pragma once

#include "core.h"

template <typename T> class sampler {
public:
  virtual T next() = 0;
};

class xorshift_sampler : public sampler<f32> {
public:
  f32 next() {
    x ^= x >> 13;
    x ^= x << 17;
    x ^= x >> 5;

    u64 float_bits = (x & 0x007FFFFF) | 0x3F800000;
    return *(f32*)&float_bits - 1.0f;
  }

private:
  u64 x{123456789};
};
