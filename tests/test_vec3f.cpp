#include <catch.hpp>

#include "core.h"
#include "vec3.h"

TEST_CASE("vec3f constructor sets all fields", "[vec3f]") {
  vec3f vec = vec3f(1.0f, 2.0f, 3.0f);

  REQUIRE(APPROX_EQ(vec.x, 1.0f));
  REQUIRE(APPROX_EQ(vec.y, 2.0f));
  REQUIRE(APPROX_EQ(vec.z, 3.0f));
}

TEST_CASE("vec3f length", "[vec3f]") {
  vec3f vec = vec3f(1.0f, 2.0f, 3.0f);
  REQUIRE(APPROX_EQ(vec.length(), 3.741657f));
}

TEST_CASE("vec3f length_sqrt", "[vec3f]") {
  vec3f vec = vec3f(1.0f, 2.0f, 3.0f);
  REQUIRE(APPROX_EQ(vec.length_sqrt(), 14.0f));
}

TEST_CASE("vec3f normalized", "[vec3f]") {
  vec3f vec = vec3f(1.0f, 2.0f, 3.0f);
  vec3f normalized = vec.normalized();

  REQUIRE(APPROX_EQ(normalized.length(), 1.0f));

  vec3f scalar = vec / normalized;
  REQUIRE(APPROX_EQ(scalar.x, scalar.y));
  REQUIRE(APPROX_EQ(scalar.y, scalar.z));
  REQUIRE(APPROX_EQ(scalar.z, scalar.x));
}

TEST_CASE("vec3f normalize", "[vec3f]") {
  vec3f vec = vec3f(1.0f, 2.0f, 3.0f);
  vec.normalize();

  REQUIRE(APPROX_EQ(vec.length(), 1.0f));

  vec3f scalar = vec3f(1.0f, 2.0f, 3.0f) / vec;
  REQUIRE(APPROX_EQ(scalar.x, scalar.y));
  REQUIRE(APPROX_EQ(scalar.y, scalar.z));
  REQUIRE(APPROX_EQ(scalar.z, scalar.x));
}

TEST_CASE("vec3f dot", "[vec3f]") {
  vec3f a = vec3f(1.0f, 0.0f, 0.0f);
  vec3f b = vec3f(0.0f, 1.0f, 0.0f);
  vec3f c = vec3f(1.0f, 2.0f, 3.0f);

  REQUIRE(APPROX_EQ(a.dot(b), 0.0f));
  REQUIRE(APPROX_EQ(c.dot(c), c.length_sqrt()));
  REQUIRE(APPROX_EQ(a.dot(c), 1.0f));
  REQUIRE(APPROX_EQ(b.dot(c), 2.0f));
}

TEST_CASE("vec3f cross", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  vec3f b = a.cross(vec3f(1.0f, 0.0, 0.0));
  vec3f c = a.cross(b);

  REQUIRE(APPROX_EQ(a.dot(b), 0.0f));
  REQUIRE(APPROX_EQ(b.dot(c), 0.0f));
  REQUIRE(APPROX_EQ(c.dot(a), 0.0f));
}

TEST_CASE("vec3f equals operator", "[vec3f]") {
  vec3f a = vec3f(1.4f, -5.7f, 3.0f);
  vec3f b = vec3f(1.4f, -5.7f, 3.0f);
  REQUIRE(a == b);
}

// vec3f vec3f operations

TEST_CASE("vec3f add vec3f", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  vec3f b = vec3f(3.0f, 2.0f, 1.0f);
  vec3f res = a + b;

  REQUIRE(res == vec3f(4.0f, 4.0f, 4.0f));
}

TEST_CASE("vec3f sub vec3f", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  vec3f b = vec3f(3.0f, 2.0f, 1.0f);
  vec3f res = a - b;

  REQUIRE(res == vec3f(-2.0f, 0.0f, 2.0f));
}

TEST_CASE("vec3f mul vec3f", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  vec3f b = vec3f(3.0f, 2.0f, 1.0f);
  vec3f res = a * b;

  REQUIRE(res == vec3f(3.0f, 4.0f, 3.0f));
}

TEST_CASE("vec3f div vec3f", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  vec3f b = vec3f(3.0f, 2.0f, 1.0f);
  vec3f res = a / b;

  REQUIRE(res == vec3f(0.33333f, 1.0f, 3.0f));
}

// vec3f f32 operations

TEST_CASE("vec3f add f32", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  vec3f res = a + 2.0f;

  REQUIRE(res == vec3f(3.0f, 4.0f, 5.0f));
}

TEST_CASE("vec3f sub f32", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  vec3f res = a - 2.0f;

  REQUIRE(res == vec3f(-1.0f, 0.0f, 1.0f));
}

TEST_CASE("vec3f mul f32", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  vec3f res = a * 2.0f;

  REQUIRE(res == vec3f(2.0f, 4.0f, 6.0f));
}

TEST_CASE("vec3f div f32", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  vec3f res = a / 2.0f;

  REQUIRE(res == vec3f(0.5f, 1.0f, 1.5f));
}

// vec3f vec3f assignment operators

TEST_CASE("vec3f add assign vec3f", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  a += vec3f(3.0f, 2.0f, 1.0f);

  REQUIRE(a == vec3f(4.0f, 4.0f, 4.0f));
}

TEST_CASE("vec3f sub assign vec3f", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  a -= vec3f(3.0f, 2.0f, 1.0f);

  REQUIRE(a == vec3f(-2.0f, 0.0f, 2.0f));
}

TEST_CASE("vec3f mul assign vec3f", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  a *= vec3f(3.0f, 2.0f, 1.0f);

  REQUIRE(a == vec3f(3.0f, 4.0f, 3.0f));
}

TEST_CASE("vec3f div assign vec3f", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  a /= vec3f(3.0f, 2.0f, 1.0f);

  REQUIRE(a == vec3f(0.33333333f, 1.0f, 3.0f));
}

// vec3f f32 assignment operators

TEST_CASE("vec3f add assign f32", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  a += 2.0f;

  REQUIRE(a == vec3f(3.0f, 4.0f, 5.0f));
}

TEST_CASE("vec3f sub assign f32", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  a -= 2.0f;

  REQUIRE(a == vec3f(-1.0f, 0.0f, 1.0f));
}

TEST_CASE("vec3f mul assign f32", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  a *= 2.0f;

  REQUIRE(a == vec3f(2.0f, 4.0f, 6.0f));
}

TEST_CASE("vec3f div assign f32", "[vec3f]") {
  vec3f a = vec3f(1.0f, 2.0f, 3.0f);
  a /= 2.0f;

  REQUIRE(a == vec3f(0.5f, 1.0f, 1.5f));
}
