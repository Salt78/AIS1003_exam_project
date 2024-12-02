#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/catch_test_macros.hpp>
#include <threepp/threepp.hpp>

#include "gridManager.hpp"

#include <geoGeneration.hpp>
#include <stdexcept>


using namespace gridManagerNS;
using namespace geoGenNS;
using namespace threepp;

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

TEST_CASE("Negative imageSize#1", "[grid]") {
    std::pair<int, int> imageSize{-354, 800};
    GridManager grid{imageSize};

    REQUIRE(grid.getCoordQuantity() == 0);

}

TEST_CASE("Mesh generation", "[scene]") {
    const std::pair<int, int> imageSize{800, 800};
    constexpr int meshQuantity{45};

    GridManager grid(imageSize);


    auto scene = Scene::create();
    GeoGen generator(*scene, grid, meshQuantity);
    generator.generateRND();

    //Help from GPT
    std::vector<Object3D *> presentMeshes = scene->children;

    REQUIRE(presentMeshes.size() == meshQuantity);
}
