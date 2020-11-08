#pragma once

#include <cmath>

#include "core.h"

template <typename T> class vec2 {
public:
  inline vec2() : x(0), y(0) {}
  inline vec2(T value) : x(value), y(value) {}
  inline vec2(T x, T y) : x(x), y(y) {}
  inline vec2(const vec2<T> &vec) : x(vec.x), y(vec.y) {}

  ~vec2() {}

  f32 length() { return sqrtf(x * x + y * y); }

  f32 length_sqrt() { return x * x + y * y; }

  f32 distance(const vec2<T> &other) {
    return sqrtf((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
  }

  vec2<T> normalized() {
    T one_over_length = 1 / sqrtf(x * x + y * y);

    return vec2<T>{
        x * one_over_length,
        y * one_over_length,
    };
  }

  void normalize() {
    T one_over_length = 1 / sqrtf(x * x + y * y);

    x *= one_over_length;
    y *= one_over_length;
  }

  T dot(const vec2<T> &other) { return x * other.x + y * other.y; }

  T &operator[](int index) {
    if (index == 0) {
      return x;
    } else if (index == 1) {
      return y;
    } else {
      UNREACHABLE();
    }
  }

  vec2<T> operator+(const vec2<T> &right) {
    return vec2<T>{
        x + right.x,
        y + right.y,
    };
  }

  vec2<T> operator-(const vec2<T> &right) {
    return vec2<T>{
        x - right.x,
        y - right.y,
    };
  }

  vec2<T> operator*(const vec2<T> &right) {
    return vec2<T>{
        x * right.x,
        y * right.y,
    };
  }

  vec2<T> operator/(const vec2<T> &right) {
    return vec2<T>{
        x / right.x,
        y / right.y,
    };
  }

  void operator+=(const vec2<T> &right) {
    x += right.x;
    y += right.y;
  }

  void operator-=(const vec2<T> &right) {
    x -= right.x;
    y -= right.y;
  }

  void operator*=(const vec2<T> &right) {
    x *= right.x;
    y *= right.y;
  }

  void operator/=(const vec2<T> &right) {
    x /= right.x;
    y /= right.y;
  }

  vec2<T> operator+(T right) {
    return vec2<T>{
        x + right,
        y + right,
    };
  }

  vec2<T> operator-(T right) {
    return vec2<T>{
        x - right,
        y - right,
    };
  }

  vec2<T> operator*(T right) {
    return vec2<T>{
        x * right,
        y * right,
    };
  }

  vec2<T> operator/(T right) {
    return vec2<T>{
        x / right,
        y / right,
    };
  }

  void operator+=(T right) {
    x += right;
    y += right;
  }

  void operator-=(T right) {
    x -= right;
    y -= right;
  }

  void operator*=(T right) {
    x *= right;
    y *= right;
  }

  void operator/=(T right) {
    x /= right;
    y /= right;
  }

public:
  T x, y;
};

template <typename T>
bool operator==(const vec2<T> &left, const vec2<T> &right) {
  return APPROX_EQ(left.x, right.x) && APPROX_EQ(left.y, right.y);
}

typedef vec2<f32> vec2f;
typedef vec2<i32> vec2i;
