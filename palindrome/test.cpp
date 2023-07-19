#include <catch.hpp>
#include <palindrome.h>

TEST_CASE("IsPalindrome") {
    REQUIRE(IsPalindrome("abba"));
    REQUIRE(IsPalindrome("a roza upala na lapu azora"));

    REQUIRE(!IsPalindrome("qwerty"));
}
