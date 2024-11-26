#include "geoDetection.hpp"
#include "geoGeneration.hpp"
#include "gridManager.hpp"
#include <keyHandler.hpp>
#include <threepp/threepp.hpp>

using namespace geoDetectionNS;
using namespace gridManagerNS;
using namespace geoGenNS;
using namespace threepp;

int main() {
    //Only nXn images are supported
    constexpr std::pair<int, int> imageSize{800, 800};

    Canvas canvas("Geometry Sorting", {{"aa", 4}, {"resizable", false}});
    canvas.setSize({imageSize.first, imageSize.second});

    GLRenderer renderer(canvas.size());
    renderer.setSize(canvas.size());

    auto scene = Scene::create();
    auto camera = OrthographicCamera::create(0, static_cast<float>(imageSize.first),
                                             0, static_cast<float>(imageSize.second), -1000, 1000);
    camera->position.z = 10;


    GridManager grid(imageSize, 15, 50);

    //GeoGen class for generating geometries at semi random locations.
    GeoGen generator{*scene, grid};
    generator.generateRND();

    GeoDetection detector("OPENCV test", imageSize);

    GeoManipulator manipulator(grid, *scene, *camera);

    KeyHandler keyHandler(generator, detector, manipulator);
    canvas.addKeyListener(keyHandler);

    canvas.animate([&]() {
        renderer.render(*scene, *camera);

        detector.setupVirtualCam(renderer);

        keyHandler.update();

        detector.imageProcessing(false);
    });
}
