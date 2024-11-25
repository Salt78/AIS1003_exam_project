#include "geoDetection.hpp"
#include "geoGeneration.hpp"
#include "gridManager.hpp"
#include "iostream"

#include <keyHandler.hpp>

using namespace geoDetectionNS;
using namespace gridManagerNS;
using namespace geoGenNS;

int main(int argc, char **argv) {
    //Only nXn images are supported
    constexpr std::pair<int, int> imageSize{800, 800};

    Canvas canvas("Geometry Sorting", {{"aa", 4}});
    canvas.setSize({imageSize.first, imageSize.second});

    GLRenderer renderer(canvas.size());
    renderer.setSize(canvas.size());

    auto scene = Scene::create();
    auto camera = OrthographicCamera::create(0, static_cast<float>(imageSize.first),
                                             0, static_cast<float>(imageSize.second), -1000, 1000);
    camera->position.z = 10;


    GridManager grid(imageSize, 15, 50);

    //GeoGen class for generating geometries at semi random locations.
    GeoGen test(40, 5, geoGenNS::Shape::CUBE, Color::aqua);
    test.generate(grid, *scene);
    GeoGen test2(40, 3, geoGenNS::Shape::CUBE, Color::red);
    test2.generate(grid, *scene);
    GeoGen test3(40, 2, geoGenNS::Shape::CUBE, Color::green);
    test3.generate(grid, *scene);
    GeoGen test4(40, 1, geoGenNS::Shape::CUBE, Color::orange);
    test4.generate(grid, *scene);

    GeoDetection detector("OPENCV test", imageSize);

    GeoManipulator manipulator(grid, *scene, *camera);

    KeyHandler keyHandler(detector, manipulator);
    canvas.addKeyListener(keyHandler);

    canvas.animate([&]() {
        renderer.render(*scene, *camera);

        detector.setupVirtualCam(renderer);

        keyHandler.update();

        detector.imageProcessing(true);




    });


}
