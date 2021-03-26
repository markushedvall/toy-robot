#include <robot/hello.h>

#include <catch2/catch.hpp>

TEST_CASE("say_hello() returns \"Hello World!\"", "[hello]") {
  REQUIRE(robot::say_hello() == "Hello World!");
}
