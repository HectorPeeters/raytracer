#include <catch.hpp>

#include "vec2.h"

TEST_CASE("vec2i constructor sets all fields", "[vec2i]") {
  vec2i vec = vec2i(1, 2);

  REQUIRE(vec.x == 1);
  REQUIRE(vec.y == 2);
}

TEST_CASE("vec2i length", "[vec2i]") {
  vec2i vec = vec2i(1, 2);
  REQUIRE(APPROX_EQ(vec.length(), 2.236068f));
}

TEST_CASE("vec2i length_sqrt", "[vec2i]") {
  vec2i vec = vec2i(1, 2);
  REQUIRE(vec.length_sqrt() == 5);
}

TEST_CASE("vec2i dot", "[vec2i]") {
  vec2i a = vec2i(1, 0);
  vec2i b = vec2i(0, 1);
  vec2i c = vec2i(1, 2);

  REQUIRE(a.dot(b) == 0);
  REQUIRE(c.dot(c) == c.length_sqrt());
  REQUIRE(a.dot(c) == 1);
  REQUIRE(b.dot(c) == 2);
}

TEST_CASE("vec2i equals operator", "[vec2i]") {
  vec2i a = vec2i(2, -4);
  vec2i b = vec2i(2, -4);
  REQUIRE(a == b);
}

// vec2i vec2i operations

TEST_CASE("vec2i add vec2i", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  vec2i b = vec2i(3, 2);
  vec2i res = a + b;

  REQUIRE(res == vec2i(4, 4));
}

TEST_CASE("vec2i sub vec2i", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  vec2i b = vec2i(3, 2);
  vec2i res = a - b;

  REQUIRE(res == vec2i(-2, 0));
}

TEST_CASE("vec2i mul vec2i", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  vec2i b = vec2i(3, 2);
  vec2i res = a * b;

  REQUIRE(res == vec2i(3, 4));
}

TEST_CASE("vec2i div vec2i", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  vec2i b = vec2i(3, 2);
  vec2i res = a / b;

  REQUIRE(res == vec2i(0, 1));
}

// vec2i i32 operations

TEST_CASE("vec2i add i32", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  vec2i res = a + 2;

  REQUIRE(res == vec2i(3, 4));
}

TEST_CASE("vec2i sub i32", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  vec2i res = a - 2;

  REQUIRE(res == vec2i(-1, 0));
}

TEST_CASE("vec2i mul i32", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  vec2i res = a * 2;

  REQUIRE(res == vec2i(2, 4));
}

TEST_CASE("vec2i div i32", "[vec2i]") {
  vec2i a = vec2i(2, 4);
  vec2i res = a / 2;

  REQUIRE(res == vec2i(1, 2));
}

// vec2i vec2i assignment operators

TEST_CASE("vec2i add assign vec2i", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  a += vec2i(3, 2);

  REQUIRE(a == vec2i(4, 4));
}

TEST_CASE("vec2i sub assign vec2i", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  a -= vec2i(3, 2);

  REQUIRE(a == vec2i(-2, 0));
}

TEST_CASE("vec2i mul assign vec2i", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  a *= vec2i(3, 2);

  REQUIRE(a == vec2i(3, 4));
}

TEST_CASE("vec2i div assign vec2i", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  a /= vec2i(3, 2);

  REQUIRE(a == vec2i(0, 1));
}

// vec2i i32 assignment operators

TEST_CASE("vec2i add assign i32", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  a += 2;

  REQUIRE(a == vec2i(3, 4));
}

TEST_CASE("vec2i sub assign i32", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  a -= 2;

  REQUIRE(a == vec2i(-1, 0));
}

TEST_CASE("vec2i mul assign i32", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  a *= 2;

  REQUIRE(a == vec2i(2, 4));
}

TEST_CASE("vec2i div assign i32", "[vec2i]") {
  vec2i a = vec2i(1, 2);
  a /= 2;

  REQUIRE(a == vec2i(0, 1));
}
