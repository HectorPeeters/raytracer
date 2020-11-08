#pragma once

#include <cmath>

#include "core.h"

template <typename T> class vec4 {
public:
  inline vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

  static inline vec4<T> zero() { return vec4<T>(0, 0, 0, 0); }

  f32 length() { return sqrtf(x * x + y * y + z * z + w * w); }

  f32 length_sqrt() { return x * x + y * y + z * z + w * w; }

  f32 distance(const vec4<T> &other) {
    return sqrtf((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) +
                 (z - other.z) * (z - other.z) + (w - other.w) * (w - other.w));
  }

  vec4<T> normalized() {
    T one_over_length = 1 / sqrtf(x * x + y * y + z * z + w * w);

    return vec4<T>{
        x * one_over_length,
        y * one_over_length,
        z * one_over_length,
        w * one_over_length,
    };
  }

  void normalize() {
    T one_over_length = 1 / sqrtf(x * x + y * y + z * z + w * w);

    x *= one_over_length;
    y *= one_over_length;
    z *= one_over_length;
    w *= one_over_length;
  }

  T dot(const vec4<T> &other) {
    return x * other.x + y * other.y + z * other.z + w * other.w;
  }

  T &operator[](int index) {
    if (index == 0) {
      return x;
    } else if (index == 1) {
      return y;
    } else if (index == 2) {
      return z;
    } else if (index == 3) {
      return w;
    } else {
      UNREACHABLE();
    }
  }

  vec4<T> operator+(const vec4<T> &right) {
    return vec4<T>{
        x + right.x,
        y + right.y,
        z + right.z,
        w + right.w,
    };
  }

  vec4<T> operator-(const vec4<T> &right) {
    return vec4<T>{
        x - right.x,
        y - right.y,
        z - right.z,
        w - right.w,
    };
  }

  vec4<T> operator*(const vec4<T> &right) {
    return vec4<T>{
        x * right.x,
        y * right.y,
        z * right.z,
        w * right.w,
    };
  }

  vec4<T> operator/(const vec4<T> &right) {
    return vec4<T>{
        x / right.x,
        y / right.y,
        z / right.z,
        w / right.w,
    };
  }

  void operator+=(const vec4<T> &right) {
    x += right.x;
    y += right.y;
    z += right.z;
    w += right.w;
  }

  void operator-=(const vec4<T> &right) {
    x -= right.x;
    y -= right.y;
    z -= right.z;
    w -= right.w;
  }

  void operator*=(const vec4<T> &right) {
    x *= right.x;
    y *= right.y;
    z *= right.z;
    w *= right.w;
  }

  void operator/=(const vec4<T> &right) {
    x /= right.x;
    y /= right.y;
    z /= right.z;
    w /= right.w;
  }

  vec4<T> operator+(T right) {
    return vec4<T>{
        x + right,
        y + right,
        z + right,
        w + right,
    };
  }

  vec4<T> operator-(T right) {
    return vec4<T>{
        x - right,
        y - right,
        z - right,
        w - right,
    };
  }

  vec4<T> operator*(T right) {
    return vec4<T>{
        x * right,
        y * right,
        z * right,
        w * right,
    };
  }

  vec4<T> operator/(T right) {
    return vec4<T>{
        x / right,
        y / right,
        z / right,
        w / right,
    };
  }

  void operator+=(T right) {
    x += right;
    y += right;
    z += right;
    w += right;
  }

  void operator-=(T right) {
    x -= right;
    y -= right;
    z -= right;
    w -= right;
  }

  void operator*=(T right) {
    x *= right;
    y *= right;
    z *= right;
    w *= right;
  }

  void operator/=(T right) {
    x /= right;
    y /= right;
    z /= right;
    w /= right;
  }

public:
  T x, y, z, w;
};

template <typename T>
bool operator==(const vec4<T> &left, const vec4<T> &right) {
  return APPROX_EQ(left.x, right.x) && APPROX_EQ(left.y, right.y) &&
         APPROX_EQ(left.z, right.z) && APPROX_EQ(left.w, right.w);
}

typedef vec4<f32> vec4f;
typedef vec4<i32> vec4i;
