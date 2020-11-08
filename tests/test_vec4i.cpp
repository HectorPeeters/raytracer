#include <catch.hpp>

#include "core.h"
#include "math/vec4.h"

TEST_CASE("vec4i constructor sets all fields", "[vec4i]") {
  vec4i vec = vec4i(1, 2, 3, 4.0);

  REQUIRE(APPROX_EQ(vec.x, 1));
  REQUIRE(APPROX_EQ(vec.y, 2));
  REQUIRE(APPROX_EQ(vec.z, 3));
  REQUIRE(APPROX_EQ(vec.w, 4));
}

TEST_CASE("vec4i length", "[vec4i]") {
  vec4i vec = vec4i(1, 2, 3, 4);
  REQUIRE(APPROX_EQ(vec.length(), 5.477226f));
}

TEST_CASE("vec4i length_sqrt", "[vec4i]") {
  vec4i vec = vec4i(1, 2, 3, 4);
  REQUIRE(APPROX_EQ(vec.length_sqrt(), 30));
}
TEST_CASE("vec4i dot", "[vec4i]") {
  vec4i a = vec4i(1, 0, 0, 0);
  vec4i b = vec4i(0, 1, 0, 0);
  vec4i c = vec4i(1, 2, 3, 4);

  REQUIRE(APPROX_EQ(a.dot(b), 0));
  REQUIRE(APPROX_EQ(c.dot(c), c.length_sqrt()));
  REQUIRE(APPROX_EQ(a.dot(c), 1));
  REQUIRE(APPROX_EQ(b.dot(c), 2));
}

TEST_CASE("vec4i index accessor", "[vec4i]}") {
  vec4i vec = vec4i(1, 2, 3, 4);

  REQUIRE(APPROX_EQ(vec[0], 1));
  REQUIRE(APPROX_EQ(vec[1], 2));
  REQUIRE(APPROX_EQ(vec[2], 3));
  REQUIRE(APPROX_EQ(vec[3], 4));
}

TEST_CASE("vec4i equals operator", "[vec4i]") {
  vec4i a = vec4i(1, -5, 3, -4);
  vec4i b = vec4i(1, -5, 3, -4);
  REQUIRE(a == b);
}

// vec4i vec4i operations

TEST_CASE("vec4i add vec4i", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  vec4i b = vec4i(4, 3, 2, 1);
  vec4i res = a + b;

  REQUIRE(res == vec4i(5, 5, 5, 5));
}

TEST_CASE("vec4i sub vec4i", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  vec4i b = vec4i(4, 3, 2, 1);
  vec4i res = a - b;

  REQUIRE(res == vec4i(-3, -1, 1, 3));
}

TEST_CASE("vec4i mul vec4i", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  vec4i b = vec4i(4, 3, 2, 1);
  vec4i res = a * b;

  REQUIRE(res == vec4i(4, 6, 6, 4));
}

TEST_CASE("vec4i div vec4i", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  vec4i b = vec4i(4, 3, 2, 1);
  vec4i res = a / b;

  REQUIRE(res == vec4i(0, 0, 1, 4));
}

// vec4i i32 operations

TEST_CASE("vec4i add i32", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  vec4i res = a + 2;

  REQUIRE(res == vec4i(3, 4, 5, 6));
}

TEST_CASE("vec4i sub i32", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  vec4i res = a - 2;

  REQUIRE(res == vec4i(-1, 0, 1, 2));
}

TEST_CASE("vec4i mul i32", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  vec4i res = a * 2;

  REQUIRE(res == vec4i(2, 4, 6, 8));
}

TEST_CASE("vec4i div i32", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  vec4i res = a / 2;

  REQUIRE(res == vec4i(0, 1, 1, 2));
}

// vec4i vec4i assignment operators

TEST_CASE("vec4i add assign vec4i", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  a += vec4i(4, 3, 2, 1);

  REQUIRE(a == vec4i(5, 5, 5, 5));
}

TEST_CASE("vec4i sub assign vec4i", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  a -= vec4i(4, 3, 2, 1);

  REQUIRE(a == vec4i(-3, -1, 1, 3));
}

TEST_CASE("vec4i mul assign vec4i", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  a *= vec4i(4, 3, 2, 1);

  REQUIRE(a == vec4i(4, 6, 6, 4));
}

TEST_CASE("vec4i div assign vec4i", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  a /= vec4i(4, 3, 2, 1);

  REQUIRE(a == vec4i(0, 0, 1, 4));
}

// vec4i float assignment operators

TEST_CASE("vec4i add assign i32", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  a += 2;

  REQUIRE(a == vec4i(3, 4, 5, 6));
}

TEST_CASE("vec4i sub assign i32", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  a -= 2;

  REQUIRE(a == vec4i(-1, 0, 1, 2));
}

TEST_CASE("vec4i mul assign i32", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  a *= 2;

  REQUIRE(a == vec4i(2, 4, 6, 8));
}

TEST_CASE("vec4i div assign i32", "[vec4i]") {
  vec4i a = vec4i(1, 2, 3, 4);
  a /= 2;

  REQUIRE(a == vec4i(0, 1, 1, 2));
}
