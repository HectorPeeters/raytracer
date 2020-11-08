#include <catch.hpp>

#include "math/vec3.h"

TEST_CASE("vec3i constructor sets all fields", "[vec3i]") {
  vec3i vec = vec3i(1, 2, 3);

  REQUIRE(vec.x == 1);
  REQUIRE(vec.y == 2);
  REQUIRE(vec.z == 3);
}

TEST_CASE("vec3i length", "[vec3i]") {
  vec3i vec = vec3i(1, 2, 3);
  REQUIRE(APPROX_EQ(vec.length(), 3.741657f));
}

TEST_CASE("vec3i length_sqrt", "[vec3i]") {
  vec3i vec = vec3i(1, 2, 3);
  REQUIRE(vec.length_sqrt() == 14);
}

TEST_CASE("vec3i dot", "[vec3i]") {
  vec3i a = vec3i(1, 0, 0);
  vec3i b = vec3i(0, 1, 0);
  vec3i c = vec3i(1, 2, 3);

  REQUIRE(a.dot(b) == 0);
  REQUIRE(c.dot(c) == c.length_sqrt());
  REQUIRE(a.dot(c) == 1);
  REQUIRE(b.dot(c) == 2);
}

TEST_CASE("vec3i cross", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  vec3i b = a.cross(vec3i(1, 0.0, 0.0));
  vec3i c = a.cross(b);

  REQUIRE(a.dot(b) == 0);
  REQUIRE(b.dot(c) == 0);
  REQUIRE(c.dot(a) == 0);
}

TEST_CASE("vec3i index accessor", "[vec3f]}") {
  vec3i vec = vec3i(1, 2, 3);

  REQUIRE(APPROX_EQ(vec[0], 1));
  REQUIRE(APPROX_EQ(vec[1], 2));
  REQUIRE(APPROX_EQ(vec[2], 3));
}

TEST_CASE("vec3i equals operator", "[vec3i]") {
  vec3i a = vec3i(2, -4, 3);
  vec3i b = vec3i(2, -4, 3);
  REQUIRE(a == b);
}

// vec3i vec3i operations

TEST_CASE("vec3i add vec3i", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  vec3i b = vec3i(3, 2, 1);
  vec3i res = a + b;

  REQUIRE(res == vec3i(4, 4, 4));
}

TEST_CASE("vec3i sub vec3i", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  vec3i b = vec3i(3, 2, 1);
  vec3i res = a - b;

  REQUIRE(res == vec3i(-2, 0, 2));
}

TEST_CASE("vec3i mul vec3i", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  vec3i b = vec3i(3, 2, 1);
  vec3i res = a * b;

  REQUIRE(res == vec3i(3, 4, 3));
}

TEST_CASE("vec3i div vec3i", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  vec3i b = vec3i(3, 2, 1);
  vec3i res = a / b;

  REQUIRE(res == vec3i(0, 1, 3));
}

// vec3i i32 operations

TEST_CASE("vec3i add i32", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  vec3i res = a + 2;

  REQUIRE(res == vec3i(3, 4, 5));
}

TEST_CASE("vec3i sub i32", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  vec3i res = a - 2;

  REQUIRE(res == vec3i(-1, 0, 1));
}

TEST_CASE("vec3i mul i32", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  vec3i res = a * 2;

  REQUIRE(res == vec3i(2, 4, 6));
}

TEST_CASE("vec3i div i32", "[vec3i]") {
  vec3i a = vec3i(2, 4, 8);
  vec3i res = a / 2;

  REQUIRE(res == vec3i(1, 2, 4));
}

// vec3i vec3i assignment operators

TEST_CASE("vec3i add assign vec3i", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  a += vec3i(3, 2, 1);

  REQUIRE(a == vec3i(4, 4, 4));
}

TEST_CASE("vec3i sub assign vec3i", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  a -= vec3i(3, 2, 1);

  REQUIRE(a == vec3i(-2, 0, 2));
}

TEST_CASE("vec3i mul assign vec3i", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  a *= vec3i(3, 2, 1);

  REQUIRE(a == vec3i(3, 4, 3));
}

TEST_CASE("vec3i div assign vec3i", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  a /= vec3i(3, 2, 1);

  REQUIRE(a == vec3i(0, 1, 3));
}

// vec3i i32 assignment operators

TEST_CASE("vec3i add assign i32", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  a += 2;

  REQUIRE(a == vec3i(3, 4, 5));
}

TEST_CASE("vec3i sub assign i32", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  a -= 2;

  REQUIRE(a == vec3i(-1, 0, 1));
}

TEST_CASE("vec3i mul assign i32", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  a *= 2;

  REQUIRE(a == vec3i(2, 4, 6));
}

TEST_CASE("vec3i div assign i32", "[vec3i]") {
  vec3i a = vec3i(1, 2, 3);
  a /= 2;

  REQUIRE(a == vec3i(0, 1, 1));
}
