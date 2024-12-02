#include "catch2/matchers/catch_matchers.hpp"
#include <catch2/catch_test_macros.hpp>

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

TEST_CASE("Integrated test with generator and manipulator", "[detection]") {
    constexpr std::pair<int, int> imageSize{800, 800};

    Canvas canvas("", {{"headless", true}});
    canvas.setSize({imageSize.first, imageSize.second});

    GLRenderer renderer(imageSize);
    auto scene = Scene::create();

    auto camera = OrthographicCamera::create(0, static_cast<float>(imageSize.first),
                                             0, static_cast<float>(imageSize.second), -1000, 1000);
    camera->position.z = 10;

    GridManager grid(imageSize);

    int meshQuantity{40};
    GeoGen generator{*scene, grid, meshQuantity};

    REQUIRE(scene->children.size() == meshQuantity);

    GeoDetection detector(imageSize);

    //First render
    renderer.render(*scene, *camera);
    detector.setupVirtualCam(renderer);
    detector.runDetection();

    GeoManipulator manipulator{grid, *scene, *camera};
    manipulator.reArrangeMeshes(detector.getDetectedObjects());

    //Second render
    renderer.render(*scene, *camera);
    detector.setupVirtualCam(renderer);
    detector.runDetection();

    REQUIRE(detector.getDetectedObjects().size() == meshQuantity);
}