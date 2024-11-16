#include <catch2/catch_test_macros.hpp>
#include "geoGeneration.hpp"
#include "gridManager.hpp"
#include "geoDetection.hpp"


using namespace geoGenNS;
using namespace gridManagerNS;
using namespace geoDetectionNS;


/*TEST_CASE("Scene creation", "[scene]") {
    std::pair<int, int> imageSize{800, 800};
    const int meshQuantity{5};

    GridManager mainGrid("GeometrySorting", imageSize, 14, 50);
    mainGrid.createGrid();

    GeoGen test(40, meshQuantity, geoGenNS::Shape::CUBE, Color::aqua);
    test.generate(mainGrid);

    std::vector<Object3D *> presentMeshes = mainGrid.getScene()->children;

    REQUIRE(presentMeshes.size() == meshQuantity);
}*/


TEST_CASE("Grid creation", "[grid]") {
    std::pair<int, int> imageSize{800, 800};

    GridManager mainGrid("GeometrySorting", imageSize, 14, 50);
    mainGrid.createGrid();

    REQUIRE(mainGrid.getCoordQuantity() == 196);
    REQUIRE(mainGrid.isUsed(1) == false);
    REQUIRE(mainGrid.getCoords(1) == std::pair<float, float>(50, 50));
    REQUIRE(mainGrid.isUsed(1) == true);
}
