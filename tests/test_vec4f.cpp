#include <catch.hpp>

#include "core.h"
#include "math/vec4.h"

TEST_CASE("vec4f constructor sets all fields", "[vec4f]") {
  vec4f vec = vec4f(1.0f, 2.0f, 3.0f, 4.0);

  REQUIRE(APPROX_EQ(vec.x, 1.0f));
  REQUIRE(APPROX_EQ(vec.y, 2.0f));
  REQUIRE(APPROX_EQ(vec.z, 3.0f));
  REQUIRE(APPROX_EQ(vec.w, 4.0f));
}

TEST_CASE("vec4f length", "[vec4f]") {
  vec4f vec = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  REQUIRE(APPROX_EQ(vec.length(), 5.477226f));
}

TEST_CASE("vec4f length_sqrt", "[vec4f]") {
  vec4f vec = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  REQUIRE(APPROX_EQ(vec.length_sqrt(), 30.0f));
}

TEST_CASE("vec4f normalized", "[vec4f]") {
  vec4f vec = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  vec4f normalized = vec.normalized();

  REQUIRE(APPROX_EQ(normalized.length(), 1.0f));

  vec4f scalar = vec / normalized;
  REQUIRE(APPROX_EQ(scalar.x, scalar.y));
  REQUIRE(APPROX_EQ(scalar.y, scalar.z));
  REQUIRE(APPROX_EQ(scalar.z, scalar.x));
}

TEST_CASE("vec4f normalize", "[vec4f]") {
  vec4f vec = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  vec.normalize();

  REQUIRE(APPROX_EQ(vec.length(), 1.0f));

  vec4f scalar = vec4f(1.0f, 2.0f, 3.0f, 4.0f) / vec;
  REQUIRE(APPROX_EQ(scalar.x, scalar.y));
  REQUIRE(APPROX_EQ(scalar.y, scalar.z));
  REQUIRE(APPROX_EQ(scalar.z, scalar.x));
}

TEST_CASE("vec4f dot", "[vec4f]") {
  vec4f a = vec4f(1.0f, 0.0f, 0.0f, 0.0f);
  vec4f b = vec4f(0.0f, 1.0f, 0.0f, 0.0f);
  vec4f c = vec4f(1.0f, 2.0f, 3.0f, 4.0f);

  REQUIRE(APPROX_EQ(a.dot(b), 0.0f));
  REQUIRE(APPROX_EQ(c.dot(c), c.length_sqrt()));
  REQUIRE(APPROX_EQ(a.dot(c), 1.0f));
  REQUIRE(APPROX_EQ(b.dot(c), 2.0f));
}

TEST_CASE("vec4f index accessor", "[vec4f]}") {
  vec4f vec = vec4f(1.0f, 2.0f, 3.0f, 4.0f);

  REQUIRE(APPROX_EQ(vec[0], 1.0f));
  REQUIRE(APPROX_EQ(vec[1], 2.0f));
  REQUIRE(APPROX_EQ(vec[2], 3.0f));
  REQUIRE(APPROX_EQ(vec[3], 4.0f));
}

TEST_CASE("vec4f equals operator", "[vec4f]") {
  vec4f a = vec4f(1.4f, -5.7f, 3.0f, -4.94f);
  vec4f b = vec4f(1.4f, -5.7f, 3.0f, -4.94f);
  REQUIRE(a == b);
}

// vec4f vec4f operations

TEST_CASE("vec4f add vec4f", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  vec4f b = vec4f(4.0f, 3.0f, 2.0f, 1.0f);
  vec4f res = a + b;

  REQUIRE(res == vec4f(5.0f, 5.0f, 5.0f, 5.0f));
}

TEST_CASE("vec4f sub vec4f", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  vec4f b = vec4f(4.0f, 3.0f, 2.0f, 1.0f);
  vec4f res = a - b;

  REQUIRE(res == vec4f(-3.0f, -1.0f, 1.0f, 3.0f));
}

TEST_CASE("vec4f mul vec4f", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  vec4f b = vec4f(4.0f, 3.0f, 2.0f, 1.0f);
  vec4f res = a * b;

  REQUIRE(res == vec4f(4.0f, 6.0f, 6.0f, 4.0f));
}

TEST_CASE("vec4f div vec4f", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  vec4f b = vec4f(4.0f, 3.0f, 2.0f, 1.0f);
  vec4f res = a / b;

  REQUIRE(res == vec4f(0.25f, 0.66666666f, 1.5f, 4.0f));
}

// vec4f f32 operations

TEST_CASE("vec4f add f32", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  vec4f res = a + 2.0f;

  REQUIRE(res == vec4f(3.0f, 4.0f, 5.0f, 6.0f));
}

TEST_CASE("vec4f sub f32", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  vec4f res = a - 2.0f;

  REQUIRE(res == vec4f(-1.0f, 0.0f, 1.0f, 2.0f));
}

TEST_CASE("vec4f mul f32", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  vec4f res = a * 2.0f;

  REQUIRE(res == vec4f(2.0f, 4.0f, 6.0f, 8.0f));
}

TEST_CASE("vec4f div f32", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  vec4f res = a / 2.0f;

  REQUIRE(res == vec4f(0.5f, 1.0f, 1.5f, 2.0f));
}

// vec4f vec4f assignment operators

TEST_CASE("vec4f add assign vec4f", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  a += vec4f(4.0f, 3.0f, 2.0f, 1.0f);

  REQUIRE(a == vec4f(5.0f, 5.0f, 5.0f, 5.0f));
}

TEST_CASE("vec4f sub assign vec4f", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  a -= vec4f(4.0f, 3.0f, 2.0f, 1.0f);

  REQUIRE(a == vec4f(-3.0f, -1.0f, 1.0f, 3.0f));
}

TEST_CASE("vec4f mul assign vec4f", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  a *= vec4f(4.0f, 3.0f, 2.0f, 1.0f);

  REQUIRE(a == vec4f(4.0f, 6.0f, 6.0f, 4.0f));
}

TEST_CASE("vec4f div assign vec4f", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  a /= vec4f(4.0f, 3.0f, 2.0f, 1.0f);

  REQUIRE(a == vec4f(0.25f, 0.666666f, 1.5f, 4.0f));
}

// vec4f f32 assignment operators

TEST_CASE("vec4f add assign f32", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  a += 2.0f;

  REQUIRE(a == vec4f(3.0f, 4.0f, 5.0f, 6.0f));
}

TEST_CASE("vec4f sub assign f32", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  a -= 2.0f;

  REQUIRE(a == vec4f(-1.0f, 0.0f, 1.0f, 2.0f));
}

TEST_CASE("vec4f mul assign f32", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  a *= 2.0f;

  REQUIRE(a == vec4f(2.0f, 4.0f, 6.0f, 8.0f));
}

TEST_CASE("vec4f div assign f32", "[vec4f]") {
  vec4f a = vec4f(1.0f, 2.0f, 3.0f, 4.0f);
  a /= 2.0f;

  REQUIRE(a == vec4f(0.5f, 1.0f, 1.5f, 2.0f));
}
