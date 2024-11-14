#include "threepp/threepp.hpp"
#include "geoGeneration.hpp"
#include "gridManager.hpp"
#include "geoDetection.hpp"

using namespace threepp;
using namespace cv;
using namespace geoDetectionNS;
using namespace gridManagerNS;
using namespace geoGenNS;

int main(int argc, char **argv) {
    constexpr std::pair<int, int> imageSize{800, 800};


    GridManager mainGrid("GeometrySorting", imageSize, 15, 50);
    mainGrid.createGrid();

    //GeoGen class for generating "random geometries"
    GeoGen test(40, 3, geoGenNS::Shape::CUBE, Color::aqua);
    test.generate(mainGrid);
    GeoGen test2(40, 3, geoGenNS::Shape::CUBE, Color::red);
    test2.generate(mainGrid);
    GeoGen test3(40, 3, geoGenNS::Shape::CIRCLE, Color::green);
    test3.generate(mainGrid);
    GeoGen test4(40, 3, geoGenNS::Shape::CUBE, Color::orange);
    test4.generate(mainGrid);

    GeoDetection mainScene("OPENCV test", imageSize);

    mainGrid.startAnimation([&]() {
        mainScene.imageProcessing();
    });
}
