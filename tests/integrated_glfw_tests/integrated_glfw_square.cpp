#include "catch2/matchers/catch_matchers.hpp"
#include <catch2/catch_test_macros.hpp>
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include "geoDetection.hpp"
#include "geoGeneration.hpp"
#include "geoManipulator.hpp"
#include "gridManager.hpp"

#include "threepp/threepp.hpp"
#include <opencv2/core.hpp>


using namespace geoGenNS;
using namespace gridManagerNS;
using namespace geoDetectionNS;
using namespace geoManipulatorNS;
using namespace threepp;
using namespace cv;

TEST_CASE("move square with manipulator", "[glfw]") {
    std::pair<int, int> imageSize{800, 800};

    Canvas canvas("", {{"headless", true}});
    canvas.setSize({imageSize.first, imageSize.second});


    GLRenderer renderer(imageSize);
    auto scene = Scene::create();

    auto camera = OrthographicCamera::create(0, static_cast<float>(imageSize.first),
                                             0, static_cast<float>(imageSize.second), -1000, 1000);
    camera->position.z = 10;

    auto material = MeshBasicMaterial::create();
    material->color = Color::aqua;
    material->side = Side::Double;

    auto geometry = SphereGeometry::create(20);

    auto mesh = Mesh::create(geometry, material);
    mesh->position.x = 400;
    mesh->position.y = 400;

    scene->add(mesh);

    GridManager grid(imageSize);
    GeoDetection detector(imageSize);

    //FIrst render
    renderer.render(*scene, *camera);
    detector.setupVirtualCam(renderer);
    detector.runDetection();

    GeoManipulator manipulator{grid, (*scene), (*camera)};
    manipulator.reArrangeMeshes(detector.getDetectedObjects());

    //Second render
    renderer.render(*scene, *camera);
    detector.setupVirtualCam(renderer);
    detector.runDetection();

    auto movedMesh = detector.getDetectedObjects();

    Point topLeft = movedMesh[0].getObject().tl();
    Point bottomRight = movedMesh[0].getObject().br();
    Point centerMesh = {bottomRight.x - topLeft.x, bottomRight.y - topLeft.y};

    REQUIRE_THAT(centerMesh.x,
                 Catch::Matchers::WithinRel(25, 0.5f));
    REQUIRE_THAT(centerMesh.y,
                 Catch::Matchers::WithinRel(25, 0.5f));
}
