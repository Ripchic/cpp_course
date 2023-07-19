#include <catch.hpp>
#include <password.h>

TEST_CASE("ValidatePassword") {
    REQUIRE(!ValidatePassword(""));
    REQUIRE(!ValidatePassword("qwerty"));

    REQUIRE(ValidatePassword("Aa1!Bb2@"));
    REQUIRE(ValidatePassword("Aa!Aa!Aa!"));
}
