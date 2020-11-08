#pragma once

#include <cmath>

#include "core.h"
#include "vec3.h"
#include "vec4.h"

template <typename T> class mat4 {
public:
  inline mat4() {}
  inline mat4(vec4<T> r0, vec4<T> r1, vec4<T> r2, vec4<T> r3)
      : r0(r0), r1(r1), r2(r2), r3(r3) {}
  ~mat4() {}

  static mat4<T> zero() {
    return mat4<T>{
        vec4<T>(0),
        vec4<T>(0),
        vec4<T>(0),
        vec4<T>(0),
    };
  }

  static mat4<T> identity() {
    return mat4<T>{
        vec4<T>(1, 0, 0, 0),
        vec4<T>(0, 1, 0, 0),
        vec4<T>(0, 0, 1, 0),
        vec4<T>(0, 0, 0, 1),
    };
  }

  static mat4<T> translation(vec3<T> translation) {
    mat4<T> result = mat4<T>::identity();
    result.r0[3] = translation.x;
    result.r1[3] = translation.y;
    result.r2[3] = translation.z;
    return result;
  }

  static mat4<T> rotation_x(T angle) {
    mat4<T> result = mat4<T>::identity();
    result.r1[1] = cos(angle);
    result.r1[2] = -sin(angle);
    result.r2[1] = sin(angle);
    result.r2[2] = cos(angle);
    return identity();
  }

  static mat4<T> rotation_y(T angle) {
    mat4<T> result = mat4<T>::identity();
    result.r0[0] = cos(angle);
    result.r0[2] = sin(angle);
    result.r2[0] = -sin(angle);
    result.r2[2] = cos(angle);
    return identity();
  }

  static mat4<T> rotation_z(T angle) {
    mat4<T> result = mat4<T>::identity();
    result.r0[0] = cos(angle);
    result.r0[1] = sin(angle);
    result.r1[0] = -sin(angle);
    result.r1[1] = cos(angle);
    return identity();
  }

  static mat4<T> rotation_euler(vec3<T> angles) {
    return rotation_x(angles.x) * rotation_y(angles.y) * rotation_z(angles.z);
  }

  static mat4<T> scale(vec3<T> scale) {
    mat4<T> result = mat4<T>::identity();
    result.r0[0] = scale.x;
    result.r1[1] = scale.y;
    result.r2[2] = scale.z;
    return result;
  }

  static mat4<T> orthographic(T left, T right, T top, T bottom, T near, T far) {
    mat4<T> result = mat4<T>::identity();

    result.r0[0] = 2 / (right - left);
    result.r1[3] = -(right + left) / (right - left);

    result.r1[1] = 2 / (top - bottom);
    result.r1[3] = -(top + bottom) / (top - bottom);

    result.r2[2] = -2 / (near - far);
    result.r2[3] = -(far + near) / (far - near);

    return result;
  }

  static mat4<T> perspective(T fov, T aspect, T near, T far) {
    mat4<T> result = mat4<T>::identity();

    T tan_half_fov = tan(fov / 2);

    result.r0[0] = 1 / (aspect * tan_half_fov);
    result.r1[1] = 1 / tan_half_fov;
    result.r2[2] = -(far + near) / (far - near);
    result.r2[3] = -(2 * far * near) / (far - near);
    result.r3[2] = -1;

    return result;
  }

  mat4<T> transpose() const {
    return mat4<T>{
        vec4<T>{r0[0], r1[0], r2[0], r3[0]},
        vec4<T>{r0[1], r1[1], r2[1], r3[1]},
        vec4<T>{r0[2], r1[2], r2[2], r3[2]},
        vec4<T>{r0[3], r1[3], r2[3], r3[3]},
    };
  }

  mat4<T> adjoint() const {
    T t00 = r2[2] * r3[3] - r3[2] * r2[3];
    T t01 = r2[1] * r3[3] - r3[1] * r2[3];
    T t02 = r2[1] * r3[2] - r3[1] * r2[2];
    T t03 = r2[0] * r3[3] - r3[0] * r2[3];
    T t04 = r2[0] * r3[2] - r3[0] * r2[2];
    T t05 = r2[0] * r3[1] - r3[0] * r2[1];
    T t06 = r1[2] * r3[3] - r3[2] * r1[3];
    T t07 = r1[1] * r3[3] - r3[1] * r1[3];
    T t08 = r1[1] * r3[2] - r3[1] * r1[2];
    T t09 = r1[0] * r3[3] - r3[0] * r1[3];
    T t10 = r1[0] * r3[2] - r3[0] * r1[2];
    T t11 = r1[0] * r3[1] - r3[0] * r1[1];
    T t12 = r1[2] * r2[3] - r2[2] * r1[3];
    T t13 = r1[1] * r2[3] - r2[1] * r1[3];
    T t14 = r1[1] * r2[2] - r2[1] * r1[2];
    T t15 = r1[0] * r2[3] - r2[0] * r1[3];
    T t16 = r1[0] * r2[2] - r2[0] * r1[2];
    T t17 = r1[0] * r2[1] - r2[0] * r1[1];

    vec4<T> res_r0{
        r1[1] * t00 - r1[2] * t01 + r1[3] * t02,
        -(r0[1] * t00 - r0[2] * t01 + r0[3] * t02),
        r0[1] * t06 - r0[2] * t07 + r0[3] * t08,
        -(r0[1] * t12 - r0[2] * t13 + r0[3] * t14),
    };

    vec4<T> res_r1{
        -(r1[0] * t00 - r1[2] * t03 + r1[3] * t04),
        r0[0] * t00 - r0[2] * t03 + r0[3] * t04,
        -(r0[0] * t06 - r0[2] * t09 + r0[3] * t10),
        r0[0] * t12 - r0[2] * t15 + r0[3] * t16,
    };

    vec4<T> res_r2{
        r1[0] * t01 - r1[1] * t03 + r1[3] * t05,
        -(r0[0] * t01 - r0[1] * t03 + r0[3] * t05),
        r0[0] * t07 - r0[1] * t09 + r0[3] * t11,
        -(r0[0] * t13 - r0[1] * t15 + r0[3] * t17),
    };

    vec4<T> res_r3{
        -(r1[0] * t02 - r1[1] * t04 + r1[2] * t05),
        r0[0] * t02 - r0[1] * t04 + r0[2] * t05,
        -(r0[0] * t08 - r0[1] * t10 + r0[2] * t11),
        r0[0] * t14 - r0[1] * t16 + r0[2] * t17,
    };

    return {res_r0, res_r1, res_r2, res_r3};
  }

  mat4<T> inverse() const {
    mat4<T> adjacency_matrix = adjoint();

    T det = r0[0] * adjacency_matrix.r0[0] + r1[0] * adjacency_matrix.r0[1] +
            r2[0] * adjacency_matrix.r0[2] + r3[0] * adjacency_matrix.r0[3];

    return adjacency_matrix / det;
  }

  vec4<T> &operator[](int index) {
    if (index == 0) {
      return r0;
    } else if (index == 1) {
      return r1;
    } else if (index == 2) {
      return r2;
    } else if (index == 3) {
      return r3;
    } else {
      UNREACHABLE();
    }
  }

  vec4<T> operator[](int index) const {
    if (index == 0) {
      return r0;
    } else if (index == 1) {
      return r1;
    } else if (index == 2) {
      return r2;
    } else if (index == 3) {
      return r3;
    } else {
      UNREACHABLE();
    }
  }

  friend bool operator==(const mat4<T> &left, const mat4<T> &right) {
    return left.r0 == right.r0 && left.r1 == right.r1 && left.r2 == right.r2 &&
           left.r3 == right.r3;
  }

  mat4<T> operator*(mat4<T> right) const {
    mat4<T> transposed = right.transpose();
    return mat4<T>{
        vec4<T>{r0.dot(transposed.r0), r0.dot(transposed.r1),
                r0.dot(transposed.r2), r0.dot(transposed.r3)},
        vec4<T>{r1.dot(transposed.r0), r1.dot(transposed.r1),
                r1.dot(transposed.r2), r1.dot(transposed.r3)},
        vec4<T>{r2.dot(transposed.r0), r2.dot(transposed.r1),
                r2.dot(transposed.r2), r2.dot(transposed.r3)},
        vec4<T>{r3.dot(transposed.r0), r3.dot(transposed.r1),
                r3.dot(transposed.r2), r3.dot(transposed.r3)},
    };
  }

  void operator*=(mat4<T> right) {
    mat4<T> result = this * right;
    r0 = result.r0;
    r1 = result.r1;
    r2 = result.r2;
    r3 = result.r3;
  }

  vec4<T> operator*(vec4<T> vec) const {
    return vec4<T>{
        r0.dot(vec),
        r1.dot(vec),
        r2.dot(vec),
        r3.dot(vec),
    };
  }

  mat4<T> operator*(T right) const {
    return mat4<T>{
        r0 * right,
        r1 * right,
        r2 * right,
        r3 * right,
    };
  }

  mat4<T> operator/(T right) const {
    T one_over_right = 1 / right;
    return mat4<T>{
        r0 * one_over_right,
        r1 * one_over_right,
        r2 * one_over_right,
        r3 * one_over_right,
    };
  }

  void operator*=(T right) {
    r0 *= right;
    r1 *= right;
    r2 *= right;
    r3 *= right;
  }

  void operator/=(T right) {
    r0 /= right;
    r1 /= right;
    r2 /= right;
    r3 /= right;
  }

public:
  vec4<T> r0, r1, r2, r3;
};

typedef mat4<f32> mat4f;
typedef mat4<i32> mat4i;
