#pragma once

#include <cmath>

#include "core.h"

template <typename T> class vec3 {
public:
  inline vec3() : x(0), y(0), z(0) {}
  inline vec3(T value) : x(value), y(value), z(value) {}
  inline vec3(T x, T y, T z) : x(x), y(y), z(z) {}
  inline vec3(const vec3<T> &vec) : x(vec.x), y(vec.y), z(vec.z) {}

  ~vec3() {}

  f32 length() const { return sqrtf(x * x + y * y + z * z); }

  f32 length_sqrt() const { return x * x + y * y + z * z; }

  f32 distance(const vec3<T> &other) const {
    return sqrtf((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) +
                 (z - other.z) * (z - other.z));
  }

  vec3<T> normalized() const {
    T one_over_length = 1 / sqrtf(x * x + y * y + z * z);

    return vec3<T>{
        x * one_over_length,
        y * one_over_length,
        z * one_over_length,
    };
  }

  void normalize() {
    T one_over_length = 1 / sqrtf(x * x + y * y + z * z);

    x *= one_over_length;
    y *= one_over_length;
    z *= one_over_length;
  }

  T dot(const vec3<T> &other) const {
    return x * other.x + y * other.y + z * other.z;
  }

  vec3<T> cross(const vec3<T> &other) const {
    return vec3<T>{
        y * other.z - other.y * z,
        z * other.x - other.z * x,
        x * other.y - other.x * y,
    };
  }

  T &operator[](int index) {
    if (index == 0) {
      return x;
    } else if (index == 1) {
      return y;
    } else if (index == 2) {
      return z;
    } else {
      UNREACHABLE();
    }
  }

  T operator[](int index) const {
    if (index == 0) {
      return x;
    } else if (index == 1) {
      return y;
    } else if (index == 2) {
      return z;
    } else {
      UNREACHABLE();
    }
  }

  friend bool operator==(const vec3<T> &left, const vec3<T> &right) {
    return APPROX_EQ(left.x, right.x) && APPROX_EQ(left.y, right.y) &&
           APPROX_EQ(left.z, right.z);
  }

  vec3<T> operator-() const {
    return vec3<T>{
        -x,
        -y,
        -z,
    };
  }

  vec3<T> operator+(const vec3<T> &right) const {
    return vec3<T>{
        x + right.x,
        y + right.y,
        z + right.z,
    };
  }

  vec3<T> operator-(const vec3<T> &right) const {
    return vec3<T>{
        x - right.x,
        y - right.y,
        z - right.z,
    };
  }

  vec3<T> operator*(const vec3<T> &right) const {
    return vec3<T>{
        x * right.x,
        y * right.y,
        z * right.z,
    };
  }

  vec3<T> operator/(const vec3<T> &right) const {
    return vec3<T>{
        x / right.x,
        y / right.y,
        z / right.z,
    };
  }

  void operator+=(const vec3<T> &right) {
    x += right.x;
    y += right.y;
    z += right.z;
  }

  void operator-=(const vec3<T> &right) {
    x -= right.x;
    y -= right.y;
    z -= right.z;
  }

  void operator*=(const vec3<T> &right) {
    x *= right.x;
    y *= right.y;
    z *= right.z;
  }

  void operator/=(const vec3<T> &right) {
    x /= right.x;
    y /= right.y;
    z /= right.z;
  }

  vec3<T> operator+(T right) const {
    return vec3<T>{
        x + right,
        y + right,
        z + right,
    };
  }

  vec3<T> operator-(T right) const {
    return vec3<T>{
        x - right,
        y - right,
        z - right,
    };
  }

  vec3<T> operator*(T right) const {
    return vec3<T>{
        x * right,
        y * right,
        z * right,
    };
  }

  vec3<T> operator/(T right) const {
    return vec3<T>{
        x / right,
        y / right,
        z / right,
    };
  }

  friend vec3<T> operator+(T left, const vec3<T> &right) {
    return vec3<T>{
        left + right.x,
        left + right.y,
        left + right.z,
    };
  }

  friend vec3<T> operator-(T left, const vec3<T> &right) {
    return vec3<T>{
        left - right.x,
        left - right.y,
        left - right.z,
    };
  }

  friend vec3<T> operator*(T left, const vec3<T> &right) {
    return vec3<T>{
        left * right.x,
        left * right.y,
        left * right.z,
    };
  }

  friend vec3<T> operator/(T left, const vec3<T> &right) {
    return vec3<T>{
        left / right.x,
        left / right.y,
        left / right.z,
    };
  }

  void operator+=(T right) {
    x += right;
    y += right;
    z += right;
  }

  void operator-=(T right) {
    x -= right;
    y -= right;
    z -= right;
  }

  void operator*=(T right) {
    x *= right;
    y *= right;
    z *= right;
  }

  void operator/=(T right) {
    x /= right;
    y /= right;
    z /= right;
  }

public:
  T x, y, z;
};

typedef vec3<f32> vec3f;
typedef vec3<i32> vec3i;
