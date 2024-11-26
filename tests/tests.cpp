#include "catch2/matchers/catch_matchers.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_test_macros.hpp>

#include "geoDetection.hpp"
#include "geoGeneration.hpp"
#include "gridManager.hpp"
#include "threepp/threepp.hpp"

#include <opencv2/core.hpp>


using namespace geoGenNS;
using namespace gridManagerNS;
using namespace geoDetectionNS;


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
    const int meshQuantity{45};

    GridManager grid(imageSize, 14, 50);


    auto scene = Scene::create();
    GeoGen generator(*scene, grid);
    generator.generateRND(meshQuantity);

    std::vector<Object3D *> presentMeshes = scene->children;


    /*auto intersectedMesh = presentMeshes[0]->as<Mesh>();
    std::shared_ptr<Material> mat = intersectedMesh->material();
    auto color = intersectedMesh->as<MeshBasicMaterial>();
    */

    REQUIRE(presentMeshes.size() == meshQuantity);
}

TEST_CASE("ShapeHandling"
          "[ShapeColorHandler]") {
    ShapeColorHandler handler;

    REQUIRE(handler.getColorProfile(Color::green) == std::pair<Scalar, Scalar>(Scalar(46, 0, 0), Scalar(68, 255, 255)));
    REQUIRE(handler.getColorProfile(Color::aqua) == std::pair<Scalar, Scalar>(Scalar(76, 0, 0), Scalar(90, 255, 255)));
    REQUIRE(handler.getColorProfile(Color::orange) == std::pair<Scalar, Scalar>(Scalar(13, 0, 0), Scalar(32, 255, 255)));
    REQUIRE(handler.getColorProfile(Color::red) == std::pair<Scalar, Scalar>(Scalar(0, 32, 0), Scalar(0, 255, 255)));
}


TEST_CASE("openCV_redDot", "[detection]") {
    constexpr std::pair<int, int> imageSize{800, 800};
    GeoDetection detector("OPENCV test", imageSize);

    Mat img = imread("data/testing_resources/images/redDot.png", IMREAD_COLOR);
    detector.loadImg("data/testing_resources/images/redDot.png");
    std::pair<float, float> coordsObject = {155.5, 645.3};//redDot

    detector.contourDetection();

    auto recognizedMesh = detector.getDetectedObjects();

    REQUIRE(recognizedMesh[0].getColor() == Color::red);
    REQUIRE(recognizedMesh[0].getShape() == ShapeColorHandler::Shapes::CIRCLE);

    Point topLeftCorner = {recognizedMesh[0].getObject().tl()};
    Point bottomRightCorner = {recognizedMesh[0].getObject().br()};

    std::pair<float, float> centerOfMesh = {(topLeftCorner.x + bottomRightCorner.x) / 2, (topLeftCorner.y + bottomRightCorner.y) / 2};

    REQUIRE_THAT(coordsObject.first,
                 Catch::Matchers::WithinRel(centerOfMesh.first, 0.1f));
    REQUIRE_THAT(coordsObject.second,
                 Catch::Matchers::WithinRel(centerOfMesh.second, 0.1f));
}


TEST_CASE("OPENCV detection with raycasting", "[detection]") {
    constexpr std::pair<int, int> imageSize{800, 800};

    Canvas canvas("", {{"headless", true}});
    canvas.setSize({imageSize.first, imageSize.second});

    GLRenderer renderer(imageSize);
    auto scene = Scene::create();

    auto camera = OrthographicCamera::create(0, static_cast<float>(imageSize.first),
                                             0, static_cast<float>(imageSize.second), -1000, 1000);
    camera->position.z = 10;


    GridManager grid(imageSize, 15, 50);

    GeoDetection detector("OPENCV test", imageSize);
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
    detector.contourDetection();

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
    if (!intersect.empty()) {
        auto objectPtr = intersect[0].object;
        if (objectPtr) {
            auto intersectedMesh = objectPtr->as<Mesh>();
            if (intersectedMesh) {
                auto newOwner = std::dynamic_pointer_cast<Mesh>(intersectedMesh->clone());

                DetectedObjects<std::shared_ptr<Mesh>> RetrievedMesh{};
                RetrievedMesh = DetectedObjects<std::shared_ptr<Mesh>>(newOwner, recognizedMesh[0].getShape(), recognizedMesh[0].getColor());
                position = RetrievedMesh.getObject()->position;
            }
        }
    }
    REQUIRE(position.x == coords.first);
    REQUIRE(position.y == coords.second);
}
