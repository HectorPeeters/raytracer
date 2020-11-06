#include <catch.hpp>

unsigned int factorial(unsigned int number) {
  return number > 1 ? factorial(number - 1) * number : 1;
}

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(factorial(0) == 1);
  REQUIRE(factorial(1) == 1);
  REQUIRE(factorial(2) == 2);
  REQUIRE(factorial(3) == 6);
  REQUIRE(factorial(10) == 3628800);
}
