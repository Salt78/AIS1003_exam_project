#include "threepp/threepp.hpp"
#include "geoGeneration.hpp"
#include "gridManager.hpp"
#include "geoDetection.hpp"

using namespace threepp;
using namespace cv;
using namespace geoDetectionNS;
using namespace geoGenNS;

int main(int argc, char **argv) {
    //Canvas creation
    Canvas canvas("RandomGeometry", {{"aa", 4}});
    constexpr std::pair<int, int> imageSize{800, 800};
    canvas.setSize({imageSize.first, imageSize.second});

    //Renderer creation
    GLRenderer renderer(canvas.size());

    //Creates scene
    auto scene= Scene::create();

    //Orthographic camera
    auto camera = OrthographicCamera::create(0, imageSize.first,
                                             0, imageSize.second, -1000, 1000);
    camera->position.z = 10;

    //Mapping coords to a grid
    GridManager mainGrid(imageSize.first, 15, 50);
    mainGrid.createGrid();

    //GeoGen class for generating "random geometries"
    GeoGen test(40, 10, geoGenNS::Shape::CIRCLE, Color::aqua);
    GeoGen test2(40, 15, geoGenNS::Shape::CUBE, Color::red);
    GeoGen test3(40, 4, geoGenNS::Shape::CUBE, Color::green);
    GeoGen test4(40, 4, geoGenNS::Shape::CUBE, Color::orange);
    test.generate(mainGrid, *scene);
    test2.generate(mainGrid, *scene);
    test3.generate(mainGrid, *scene);
    test4.generate(mainGrid, *scene);

    GeoDetection mainScene("OPENCV test", imageSize);


    //Render loop
    Clock clock;
    canvas.animate([&]() {
        renderer.render(*scene, *camera);

        mainScene.imageProcessing();

        waitKey(1);
    });
}
