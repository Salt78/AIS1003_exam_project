#include "geoGeneration.hpp"
#include "gridManager.hpp"
#include "geoDetection.hpp"
#include <catch2/catch_test_macros.hpp>


using namespace geoGenNS;
using namespace gridManagerNS;


TEST_CASE("Grid creation", "[grid]") {
    std::pair<int, int> imageSize{800, 800};

    GridManager mainGrid("GeometrySorting", imageSize, 14, 50);
    mainGrid.createGrid();

    REQUIRE(mainGrid.getCoordQuantity() == 196);
    REQUIRE(mainGrid.isUsed(1) == false);
    REQUIRE(mainGrid.getCoords(1) == std::pair<float, float>(50, 50));
    REQUIRE(mainGrid.isUsed(1) == true);
}


TEST_CASE("Scene creation", "[scene]") {
    std::pair<int, int> imageSizee{800, 800};
    const int meshQuantity{5};

    GridManager grid2("Scene creation", imageSizee, 14, 50);
    grid2.createGrid();

    GeoGen test(40, meshQuantity, geoGenNS::Shape::CUBE, Color::aqua);
    test.generate(grid2);

    std::vector<Object3D *> presentMeshes = grid2.getScene()->children;

    REQUIRE(presentMeshes.size() == meshQuantity);
}