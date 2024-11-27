#include "catch2/matchers/catch_matchers.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_test_macros.hpp>

#include "gridManager.hpp"

using namespace gridManagerNS;

TEST_CASE("Grid creation", "[grid]") {
    std::pair<int, int> imageSize{800, 800};

    GridManager mainGrid(imageSize, 14, 50);

    REQUIRE(mainGrid.getCoordQuantity() == 196);
    REQUIRE(mainGrid.isUsed(1) == false);
    REQUIRE(mainGrid.getCoords(1) == std::pair<float, float>(50, 50));
    REQUIRE(mainGrid.isUsed(1) == true);
}