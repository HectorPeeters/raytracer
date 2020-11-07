#include <catch.hpp>

#include "core.h"
#include "log.h"
#include "mat4.h"

TEST_CASE("mat4f constructor sets all rows", "[mat4f]") {
  mat4f mat =
      mat4f(vec4f(1.0f, 2.0f, 3.0f, 4.0f), vec4f(5.0f, 6.0f, 7.0f, 8.0f),
            vec4f(9.0f, 10.0f, 11.0f, 12.0f), vec4f(13.0f, 14.0f, 15.0f, 16.0));

  REQUIRE(mat.r0 == vec4f(1.0f, 2.0f, 3.0f, 4.0f));
  REQUIRE(mat.r1 == vec4f(5.0f, 6.0f, 7.0f, 8.0f));
  REQUIRE(mat.r2 == vec4f(9.0f, 10.0f, 11.0f, 12.0f));
  REQUIRE(mat.r3 == vec4f(13.0f, 14.0f, 15.0f, 16.0f));
}

TEST_CASE("mat4f zero sets all zeros", "[mat4f]") {
  mat4f mat = mat4f::zero();

  REQUIRE(mat.r0 == vec4f(0.0f, 0.0f, 0.0f, 0.0f));
  REQUIRE(mat.r1 == vec4f(0.0f, 0.0f, 0.0f, 0.0f));
  REQUIRE(mat.r2 == vec4f(0.0f, 0.0f, 0.0f, 0.0f));
  REQUIRE(mat.r3 == vec4f(0.0f, 0.0f, 0.0f, 0.0f));
}

TEST_CASE("mat4f identity", "[mat4f]") {
  mat4f mat = mat4f::identity();

  REQUIRE(mat.r0 == vec4f(1.0f, 0.0f, 0.0f, 0.0f));
  REQUIRE(mat.r1 == vec4f(0.0f, 1.0f, 0.0f, 0.0f));
  REQUIRE(mat.r2 == vec4f(0.0f, 0.0f, 1.0f, 0.0f));
  REQUIRE(mat.r3 == vec4f(0.0f, 0.0f, 0.0f, 1.0f));
}

TEST_CASE("mat4f translation", "[mat4f]") {
  mat4f mat = mat4f::translation(vec3f(1.0f, 2.0f, 3.0f));

  vec4f result = mat * vec4f(0.0f, 0.0f, 0.0f, 1.0f);
  REQUIRE(result == vec4f(1.0f, 2.0f, 3.0f, 1.0f));
}

TEST_CASE("mat4f scale", "[mat4f]") {
  mat4f mat = mat4f::scale(vec3f(1.0f, 2.0f, 3.0f));

  vec4f result = mat * vec4f(2.0f, 1.0f, 3.0f, 1.0f);
  REQUIRE(result == vec4f(2.0f, 2.0f, 9.0f, 1.0f));
}

TEST_CASE("mat4f transpose", "[mat4f]") {
  mat4f mat =
      mat4f(vec4f(1.0f, 2.0f, 3.0f, 4.0f), vec4f(5.0f, 6.0f, 7.0f, 8.0f),
            vec4f(9.0f, 10.0f, 11.0f, 12.0f), vec4f(13.0f, 14.0f, 15.0f, 16.0))
          .transpose();

  REQUIRE(mat.r0 == vec4f(1.0f, 5.0f, 9.0f, 13.0f));
  REQUIRE(mat.r1 == vec4f(2.0f, 6.0f, 10.0f, 14.0f));
  REQUIRE(mat.r2 == vec4f(3.0f, 7.0f, 11.0f, 15.0f));
  REQUIRE(mat.r3 == vec4f(4.0f, 8.0f, 12.0f, 16.0f));
}

TEST_CASE("mat4f adjoint", "[mat4f]") {
  mat4f mat =
      mat4f(vec4f(10.0f, 4.0f, 7.0f, 12.0f), vec4f(16.0f, 15.0f, 13.0f, 5.0f),
            vec4f(14.0f, 3.0f, 2.0f, 8.0f), vec4f(9.0f, 11.0f, 6.0f, 1.0))
          .adjoint();
  mat4f expected = mat4f(vec4f(395.0f, -363.0f, -424.0f, 467.0f),
                         vec4f(-348.0f, 738.0f, 219.0f, -1266.0f),
                         vec4f(145.0f, -906.0f, 208.0f, 1126.0f),
                         vec4f(-597.0f, 585.0f, 159.0f, -624.0f));

  REQUIRE(mat == expected);
}

TEST_CASE("mat4f inverse", "[mat4f]") {
  mat4f mat =
      mat4f(vec4f(10.0f, 4.0f, 7.0f, 12.0f), vec4f(16.0f, 15.0f, 13.0f, 5.0f),
            vec4f(14.0f, 3.0f, 2.0f, 8.0f), vec4f(9.0f, 11.0f, 6.0f, 1.0));
  mat4f inverse = mat.inverse();

  REQUIRE(mat * inverse == mat4f::identity());
}

TEST_CASE("mat4f multiply mat4f", "[mat4f]") {
  mat4f mata =
      mat4f(vec4f(1.0f, 2.0f, 3.0f, 4.0f), vec4f(5.0f, 6.0f, 7.0f, 8.0f),
            vec4f(9.0f, 10.0f, 11.0f, 12.0f), vec4f(13.0f, 14.0f, 15.0f, 16.0));
  mat4f matb =
      mat4f(vec4f(10.0f, 4.0f, 7.0f, 12.0f), vec4f(16.0f, 15.0f, 13.0f, 5.0f),
            vec4f(14.0f, 3.0f, 2.0f, 8.0f), vec4f(9.0f, 11.0f, 6.0f, 1.0));

  mat4f expected = mat4f(vec4f(120.0f, 87.0f, 63.0f, 50.0f),
                         vec4f(316.0f, 219.0f, 175.0f, 154.0f),
                         vec4f(512.0f, 351.0f, 287.0f, 258.0f),
                         vec4f(708.0f, 483.0f, 399.0f, 362.0f));

  REQUIRE(mata * matb == expected);
}

TEST_CASE("mat4f index accessor", "[mat4f]") {
  mat4f mat =
      mat4f(vec4f(1.0f, 2.0f, 3.0f, 4.0f), vec4f(5.0f, 6.0f, 7.0f, 8.0f),
            vec4f(9.0f, 10.0f, 11.0f, 12.0f), vec4f(13.0f, 14.0f, 15.0f, 16.0));

  REQUIRE(mat[0] == vec4f(1.0f, 2.0f, 3.0f, 4.0f));
  REQUIRE(mat[1] == vec4f(5.0f, 6.0f, 7.0f, 8.0f));
  REQUIRE(mat[2] == vec4f(9.0f, 10.0f, 11.0f, 12.0f));
  REQUIRE(mat[3] == vec4f(13.0f, 14.0f, 15.0f, 16.0f));
}

TEST_CASE("mat4f equals operator", "[mat4f]") {
  mat4f mat1 =
      mat4f(vec4f(1.0f, 2.0f, 3.0f, 4.0f), vec4f(5.0f, 6.0f, 7.0f, 8.0f),
            vec4f(9.0f, 10.0f, 11.0f, 12.0f), vec4f(13.0f, 14.0f, 15.0f, 16.0));

  mat4f mat2 =
      mat4f(vec4f(1.0f, 2.0f, 3.0f, 4.0f), vec4f(5.0f, 6.0f, 7.0f, 8.0f),
            vec4f(9.0f, 10.0f, 11.0f, 12.0f), vec4f(13.0f, 14.0f, 15.0f, 16.0));

  REQUIRE(mat1 == mat2);
}
