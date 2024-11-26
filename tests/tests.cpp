#include "geoGeneration.hpp"
#include "gridManager.hpp"
#include "geoDetection.hpp"
#include <catch2/catch_test_macros.hpp>


using namespace geoGenNS;
using namespace gridManagerNS;


TEST_CASE("Grid creation", "[grid]") {
    std::pair<int, int> imageSize{800, 800};

    GridManager mainGrid(imageSize, 14, 50);

    REQUIRE(mainGrid.getCoordQuantity() == 196);
    REQUIRE(mainGrid.isUsed(1) == false);
    REQUIRE(mainGrid.getCoords(1) == std::pair<float, float>(50, 50));
    REQUIRE(mainGrid.isUsed(1) == true);
}


TEST_CASE("Mesh generation", "[scene]") {
    std::pair<int, int> imageSize{800, 800};
    const int meshQuantity{5};

    GridManager grid(imageSize, 14, 50);


    auto scene = Scene::create();
    GeoGen generator(*scene, grid);
    generator.generate(meshQuantity);

    std::vector<Object3D *> presentMeshes = scene->children;


    /*auto intersectedMesh = presentMeshes[0]->as<Mesh>();
    std::shared_ptr<Material> mat = intersectedMesh->material();
    auto color = intersectedMesh->as<MeshBasicMaterial>();
    */


    REQUIRE(presentMeshes.size() == meshQuantity);
}