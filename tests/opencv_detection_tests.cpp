#include "catch2/matchers/catch_matchers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "geoDetection.hpp"
#include "geoGeneration.hpp"
#include "geoManipulator.hpp"
#include "gridManager.hpp"


#include <opencv2/core.hpp>

using namespace geoGenNS;
using namespace gridManagerNS;
using namespace geoDetectionNS;
using namespace geoManipulatorNS;
using namespace shapeColorNS;
using namespace cv;



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


