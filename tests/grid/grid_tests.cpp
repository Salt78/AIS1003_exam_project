#include "catch2/matchers/catch_matchers.hpp"
#include "gridManager.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <stdexcept>

using namespace gridManagerNS;

TEST_CASE("Intended usage", "[grid]") {
    constexpr std::pair<int, int> imageSize{800, 800};

    GridManager grid{imageSize, 50};

    REQUIRE(grid.getCoordQuantity() == 256);
    REQUIRE(grid.isUsed(1) == false);
    REQUIRE(grid.getCoords(1) == std::pair<float, float>(25, 25));
    REQUIRE(grid.isUsed(1) == true);

    grid.resetUsedCoords();
    REQUIRE(grid.isUsed(1) == false);

    REQUIRE(grid.getCoords(256) == std::pair<float, float>(775, 775));
    REQUIRE(grid.isUsed(256) == true);
}

TEST_CASE("Intended usage (non-standard params)", "[grid]") {
    constexpr std::pair<int, int> imageSize{1000, 1000};

    GridManager grid{imageSize, 50};

    REQUIRE(grid.getCoordQuantity() == 400);
    REQUIRE(grid.isUsed(1) == false);
    REQUIRE(grid.getCoords(1) == std::pair<float, float>(25, 25));
    REQUIRE(grid.isUsed(1) == true);

    grid.resetUsedCoords();
    REQUIRE(grid.isUsed(1) == false);

    REQUIRE(grid.getCoords(400) == std::pair<float, float>(975, 975));
    REQUIRE(grid.isUsed(400) == true);
}

TEST_CASE("Non-uniform imageSize", "[grid]") {
    std::pair<int, int> imageSize{500, 800};
    REQUIRE_THROWS_AS(GridManager(imageSize), std::invalid_argument);

    imageSize = {324, 214};
    REQUIRE_THROWS_AS(GridManager(imageSize), std::invalid_argument);
}

TEST_CASE("Non-positive imageSize", "[grid]") {
    std::pair<int, int> imageSize{0, 800};
    REQUIRE_THROWS_AS(GridManager(imageSize), std::invalid_argument);

    imageSize = {800, -1};
    REQUIRE_THROWS_AS(GridManager(imageSize), std::invalid_argument);
}

TEST_CASE("Invalid spacing or startCoords", "[grid]") {
    std::pair<int, int> imageSize{800, 800};

    REQUIRE_THROWS_AS(GridManager(imageSize, 0), std::invalid_argument);
    REQUIRE_THROWS_AS(GridManager(imageSize, -5), std::invalid_argument);

    REQUIRE_THROWS_AS(GridManager(imageSize, 50, {-1, 25}), std::invalid_argument);
}

TEST_CASE("Invalid configuration", "[grid]") {
    std::pair<int, int> imageSize{800, 800};
    std::pair<float, float> startingCoords{27, 25.5};

    REQUIRE_THROWS_AS(GridManager(imageSize, 50, startingCoords), std::invalid_argument);

}
TEST_CASE("undefined usage of functions", "[grid]") {
    constexpr std::pair<int, int> imageSize{800, 800};

    GridManager grid{imageSize, 50, {25, 25}};

    REQUIRE_THROWS_AS(grid.getCoords(500), std::invalid_argument);
}