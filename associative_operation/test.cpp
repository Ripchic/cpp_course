#include <catch.hpp>
#include <associative_operation.h>

TEST_CASE("Associative") {
    std::vector<std::vector<size_t>> a = {{0, 1}, {1, 0}};
    REQUIRE(IsAssociative(a));
}

TEST_CASE("NotAssociative") {
    std::vector<std::vector<size_t>> a = {{0, 0}, {1, 0}};
    REQUIRE(!IsAssociative(a));
}
