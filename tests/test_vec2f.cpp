#include <catch.hpp>

#include "core.h"
#include "math/vec2.h"

TEST_CASE("vec2f empty constructor", "[vec2f]") {
  vec2f vec = vec2f();

  REQUIRE(APPROX_EQ(vec.x, 0.0f));
  REQUIRE(APPROX_EQ(vec.y, 0.0f));
}

TEST_CASE("vec2f single value constructor", "[vec2f]") {
  vec2f vec = vec2f(2.0f);

  REQUIRE(APPROX_EQ(vec.x, 2.0f));
  REQUIRE(APPROX_EQ(vec.y, 2.0f));
}

TEST_CASE("vec2f constructor sets all fields", "[vec2f]") {
  vec2f vec = vec2f(1.0f, 2.0f);

  REQUIRE(APPROX_EQ(vec.x, 1.0f));
  REQUIRE(APPROX_EQ(vec.y, 2.0f));
}

TEST_CASE("vec2f copy constructor", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  vec2f vec(a);

  REQUIRE(APPROX_EQ(vec.x, 1.0f));
  REQUIRE(APPROX_EQ(vec.y, 2.0f));
}

TEST_CASE("vec2f length", "[vec2f]") {
  vec2f vec = vec2f(1.0f, 2.0f);
  REQUIRE(APPROX_EQ(vec.length(), 2.236068f));
}

TEST_CASE("vec2f length_sqrt", "[vec2f]") {
  vec2f vec = vec2f(1.0f, 2.0f);
  REQUIRE(APPROX_EQ(vec.length_sqrt(), 5.0f));
}

TEST_CASE("vec2f normalized", "[vec2f]") {
  vec2f vec = vec2f(1.0f, 2.0f);
  vec2f normalized = vec.normalized();

  REQUIRE(APPROX_EQ(normalized.length(), 1.0f));

  vec2f scalar = vec / normalized;
  REQUIRE(APPROX_EQ(scalar.x, scalar.y));
}

TEST_CASE("vec2f normalize", "[vec2f]") {
  vec2f vec = vec2f(1.0f, 2.0f);
  vec.normalize();

  REQUIRE(APPROX_EQ(vec.length(), 1.0f));

  vec2f scalar = vec2f(1.0f, 2.0f) / vec;
  REQUIRE(APPROX_EQ(scalar.x, scalar.y));
}

TEST_CASE("vec2f dot", "[vec2f]") {
  vec2f a = vec2f(1.0f, 0.0f);
  vec2f b = vec2f(0.0f, 1.0f);
  vec2f c = vec2f(1.0f, 2.0f);

  REQUIRE(APPROX_EQ(a.dot(b), 0.0f));
  REQUIRE(APPROX_EQ(c.dot(c), c.length_sqrt()));
  REQUIRE(APPROX_EQ(a.dot(c), 1.0f));
  REQUIRE(APPROX_EQ(b.dot(c), 2.0f));
}

TEST_CASE("vec2f index accessor", "[vec2f]}") {
  vec2f vec = vec2f(1.0f, 2.0f);

  REQUIRE(APPROX_EQ(vec[0], 1.0f));
  REQUIRE(APPROX_EQ(vec[1], 2.0f));
}

TEST_CASE("vec2f equals operator", "[vec2f]") {
  vec2f a = vec2f(1.4f, -5.7f);
  vec2f b = vec2f(1.4f, -5.7f);
  REQUIRE(a == b);
}

// vec2f vec2f operations

TEST_CASE("vec2f add vec2f", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  vec2f b = vec2f(3.0f, 2.0f);
  vec2f res = a + b;

  REQUIRE(res == vec2f(4.0f, 4.0f));
}

TEST_CASE("vec2f sub vec2f", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  vec2f b = vec2f(3.0f, 2.0f);
  vec2f res = a - b;

  REQUIRE(res == vec2f(-2.0f, 0.0f));
}

TEST_CASE("vec2f mul vec2f", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  vec2f b = vec2f(3.0f, 2.0f);
  vec2f res = a * b;

  REQUIRE(res == vec2f(3.0f, 4.0f));
}

TEST_CASE("vec2f div vec2f", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  vec2f b = vec2f(3.0f, 2.0f);
  vec2f res = a / b;

  REQUIRE(res == vec2f(0.33333f, 1.0f));
}

// vec2f f32 operations

TEST_CASE("vec2f add f32", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  vec2f res = a + 2.0f;

  REQUIRE(res == vec2f(3.0f, 4.0f));
}

TEST_CASE("vec2f sub f32", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  vec2f res = a - 2.0f;

  REQUIRE(res == vec2f(-1.0f, 0.0f));
}

TEST_CASE("vec2f mul f32", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  vec2f res = a * 2.0f;

  REQUIRE(res == vec2f(2.0f, 4.0f));
}

TEST_CASE("vec2f div f32", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  vec2f res = a / 2.0f;

  REQUIRE(res == vec2f(0.5f, 1.0f));
}

// vec2f vec2f assignment operators

TEST_CASE("vec2f add assign vec2f", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  a += vec2f(3.0f, 2.0f);

  REQUIRE(a == vec2f(4.0f, 4.0f));
}

TEST_CASE("vec2f sub assign vec2f", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  a -= vec2f(3.0f, 2.0f);

  REQUIRE(a == vec2f(-2.0f, 0.0f));
}

TEST_CASE("vec2f mul assign vec2f", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  a *= vec2f(3.0f, 2.0f);

  REQUIRE(a == vec2f(3.0f, 4.0f));
}

TEST_CASE("vec2f div assign vec2f", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  a /= vec2f(3.0f, 2.0f);

  REQUIRE(a == vec2f(0.33333333f, 1.0f));
}

// vec2f f32 assignment operators

TEST_CASE("vec2f add assign f32", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  a += 2.0f;

  REQUIRE(a == vec2f(3.0f, 4.0f));
}

TEST_CASE("vec2f sub assign f32", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  a -= 2.0f;

  REQUIRE(a == vec2f(-1.0f, 0.0f));
}

TEST_CASE("vec2f mul assign f32", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  a *= 2.0f;

  REQUIRE(a == vec2f(2.0f, 4.0f));
}

TEST_CASE("vec2f div assign f32", "[vec2f]") {
  vec2f a = vec2f(1.0f, 2.0f);
  a /= 2.0f;

  REQUIRE(a == vec2f(0.5f, 1.0f));
}
