#include "catch2/matchers/catch_matchers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

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
    GeoDetection detector(imageSize);

    SECTION("redDot.png") {
        detector.loadImg("data/testing_resources/images/redDot.png");
        std::pair<float, float> coordsObject = {155.5, 645.3};//redDot

        detector.runDetection();

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


    SECTION("greenDot.png") {
        detector.loadImg("data/testing_resources/images/greenDot.png");
        std::pair<float, float> coordsObject = {350, 400};//greenDot

        detector.runDetection();

        auto recognizedMesh = detector.getDetectedObjects();

        REQUIRE(recognizedMesh[0].getColor() == Color::green);
        REQUIRE(recognizedMesh[0].getShape() == ShapeColorHandler::Shapes::CIRCLE);

        Point topLeftCorner = {recognizedMesh[0].getObject().tl()};
        Point bottomRightCorner = {recognizedMesh[0].getObject().br()};

        std::pair<float, float> centerOfMesh = {(topLeftCorner.x + bottomRightCorner.x) / 2, (topLeftCorner.y + bottomRightCorner.y) / 2};

        REQUIRE_THAT(coordsObject.first,
                     Catch::Matchers::WithinRel(centerOfMesh.first, 0.1f));
        REQUIRE_THAT(coordsObject.second,
                     Catch::Matchers::WithinRel(centerOfMesh.second, 0.1f));
    }


    SECTION("aquaSquare.png") {
        detector.loadImg("data/testing_resources/images/aquaSquare.png");
        std::pair<float, float> coordsObject = {634.7, 132.32};//aquaSquare

        detector.runDetection();

        auto recognizedMesh = detector.getDetectedObjects();

        REQUIRE(recognizedMesh[0].getColor() == Color::aqua);
        REQUIRE(recognizedMesh[0].getShape() == ShapeColorHandler::Shapes::CUBE);

        Point topLeftCorner = {recognizedMesh[0].getObject().tl()};
        Point bottomRightCorner = {recognizedMesh[0].getObject().br()};

        std::pair<float, float> centerOfMesh = {(topLeftCorner.x + bottomRightCorner.x) / 2, (topLeftCorner.y + bottomRightCorner.y) / 2};

        REQUIRE_THAT(coordsObject.first,
                     Catch::Matchers::WithinRel(centerOfMesh.first, 0.1f));
        REQUIRE_THAT(coordsObject.second,
                     Catch::Matchers::WithinRel(centerOfMesh.second, 0.1f));
    }


    SECTION("orangeSquare.png") {
        detector.loadImg("data/testing_resources/images/orangeSquare.png");
        std::pair<float, float> coordsObject = {700, 700};//orangeSquare

        detector.runDetection();

        auto recognizedMesh = detector.getDetectedObjects();

        REQUIRE(recognizedMesh[0].getColor() == Color::orange);
        REQUIRE(recognizedMesh[0].getShape() == ShapeColorHandler::Shapes::CUBE);

        Point topLeftCorner = {recognizedMesh[0].getObject().tl()};
        Point bottomRightCorner = {recognizedMesh[0].getObject().br()};

        std::pair<float, float> centerOfMesh = {(topLeftCorner.x + bottomRightCorner.x) / 2, (topLeftCorner.y + bottomRightCorner.y) / 2};

        REQUIRE_THAT(coordsObject.first,
                     Catch::Matchers::WithinRel(centerOfMesh.first, 0.1f));
        REQUIRE_THAT(coordsObject.second,
                     Catch::Matchers::WithinRel(centerOfMesh.second, 0.1f));
    }
}


