#include "geoDetection.hpp"
#include "geoGeneration.hpp"
#include "gridManager.hpp"
#include <keyHandler.hpp>

#include <threepp/threepp.hpp>

using namespace geoDetectionNS;
using namespace gridManagerNS;
using namespace geoManipulatorNS;
using namespace geoGenNS;
using namespace threepp;

int main() {
    //Only 800x800 images are supported
    constexpr std::pair<int, int> imageSize{800, 800};

    Canvas canvas("Geometry Sorting Demo", {{"resizable", false}});
    canvas.setSize(imageSize);

    GLRenderer renderer(canvas.size());
    renderer.setSize(canvas.size());

    auto scene = Scene::create();
    auto camera = OrthographicCamera::create(0, imageSize.first, 0, imageSize.second, -1000, 1000);

    GridManager grid(imageSize);

    //Quantity of meshes can be changed here.
    GeoGen generator{*scene, grid, 100};

    GeoDetection detector(imageSize);

    GeoManipulator manipulator(grid, *scene, *camera);

    KeyHandler keyHandler{};
    canvas.addKeyListener(keyHandler);

    canvas.animate([&]() {
        renderer.render(*scene, *camera);

        detector.setupVirtualCam(renderer);
        keyHandler.update(generator, detector, manipulator);
    });
}
