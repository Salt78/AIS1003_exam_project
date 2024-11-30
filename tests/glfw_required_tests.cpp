#include "catch2/matchers/catch_matchers.hpp"
#include <catch2/catch_test_macros.hpp>

#include "geoDetection.hpp"
#include "geoGeneration.hpp"
#include "geoManipulator.hpp"
#include "gridManager.hpp"

#include "threepp/threepp.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace geoGenNS;
using namespace gridManagerNS;
using namespace geoDetectionNS;
using namespace geoManipulatorNS;
using namespace shapeColorNS;
using namespace threepp;
using namespace cv;

TEST_CASE("OPENCV detection with raycasting", "[detection]") {
    constexpr std::pair<int, int> imageSize{800, 800};

    Canvas canvas("", {{"headless", true}});
    canvas.setSize({imageSize.first, imageSize.second});

    GLRenderer renderer(imageSize);
    auto scene = Scene::create();

    auto camera = OrthographicCamera::create(0, static_cast<float>(imageSize.first),
                                             0, static_cast<float>(imageSize.second), -1000, 1000);
    camera->position.z = 10;


    GridManager grid(imageSize);

    GeoDetection detector(imageSize);
    GeoManipulator manipulator(grid, *scene, *camera);

    auto material = MeshBasicMaterial::create();
    material->side = Side::Double;
    material->color = Color::red;

    auto geometry = SphereGeometry::create(20, 32, 32);

    constexpr std::pair<float, float> coords = {100, 700};
    auto mesh = Mesh::create(geometry, material);
    mesh->position.set(coords.first, coords.second, 0);
    scene->add(mesh);

    renderer.render(*scene, *camera);

    detector.setupVirtualCam(renderer);
    detector.evalColorShape();

    auto recognizedMesh = detector.getDetectedObjects();

    REQUIRE(recognizedMesh[0].getColor() == Color::red);
    REQUIRE(recognizedMesh[0].getShape() == ShapeColorHandler::Shapes::CIRCLE);

    Raycaster raycaster;

    float flippedY = imageSize.second - coords.second;
    Vector2 ndc = {
            (coords.first / 800.0f) * 2.0f - 1.0f,// X normalized
            (flippedY / 800.0f) * 2.0f - 1.0f     // Y normalized
    };

    raycaster.setFromCamera(ndc, *camera);

    std::vector<Intersection> intersect = raycaster.intersectObjects(scene->children, false);
    Vector3 position{};

    auto objectPtr = intersect[0].object;

    auto intersectedMesh = objectPtr->as<Mesh>();

    auto newOwner = std::dynamic_pointer_cast<Mesh>(intersectedMesh->clone());

    DetectedObjects<std::shared_ptr<Mesh>> RetrievedMesh{};
    RetrievedMesh = DetectedObjects<std::shared_ptr<Mesh>>(newOwner, recognizedMesh[0].getShape(), recognizedMesh[0].getColor());
    position = RetrievedMesh.getObject()->position;


    REQUIRE(position.x == coords.first);
    REQUIRE(position.y == coords.second);
}
