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

  f32 length() { return sqrtf(x * x + y * y + z * z); }

  f32 length_sqrt() { return x * x + y * y + z * z; }

  f32 distance(const vec3<T> &other) {
    return sqrtf((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) +
                 (z - other.z) * (z - other.z));
  }

  vec3<T> normalized() {
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

  T dot(const vec3<T> &other) {
    return x * other.x + y * other.y + z * other.z;
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

  vec3<T> cross(const vec3<T> &other) {
    return vec3<T>{
        y * other.z - other.y * z,
        z * other.x - other.z * x,
        x * other.y - other.x * y,
    };
  }

  vec3<T> operator-() {
    return vec3<T>{
        -x,
        -y,
        -z,
    };
  }

  vec3<T> operator+(const vec3<T> &right) {
    return vec3<T>{
        x + right.x,
        y + right.y,
        z + right.z,
    };
  }

  vec3<T> operator-(const vec3<T> &right) {
    return vec3<T>{
        x - right.x,
        y - right.y,
        z - right.z,
    };
  }

  vec3<T> operator*(const vec3<T> &right) {
    return vec3<T>{
        x * right.x,
        y * right.y,
        z * right.z,
    };
  }

  vec3<T> operator/(const vec3<T> &right) {
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

  vec3<T> operator+(T right) {
    return vec3<T>{
        x + right,
        y + right,
        z + right,
    };
  }

  vec3<T> operator-(T right) {
    return vec3<T>{
        x - right,
        y - right,
        z - right,
    };
  }

  vec3<T> operator*(T right) {
    return vec3<T>{
        x * right,
        y * right,
        z * right,
    };
  }

  vec3<T> operator/(T right) {
    return vec3<T>{
        x / right,
        y / right,
        z / right,
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

template <typename T>
bool operator==(const vec3<T> &left, const vec3<T> &right) {
  return APPROX_EQ(left.x, right.x) && APPROX_EQ(left.y, right.y) &&
         APPROX_EQ(left.z, right.z);
}

typedef vec3<f32> vec3f;
typedef vec3<i32> vec3i;
