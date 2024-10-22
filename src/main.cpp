#include <opencv2/opencv.hpp>
#include <iostream>

#include "../cmake-build-debug/_deps/threepp-src/src/external/glad/glad/glad.h"
#include "threepp/threepp.hpp"
#include "geoGeneration.hpp"

using namespace threepp;
using namespace cv;

int main(int argc, char **argv) {
    //Canvas creation
    Canvas canvas("RandomGeometry", {{"aa", 4}});

    //Renderer creation
    GLRenderer renderer(canvas.size());
    std::pair<int, int> imageSize{1920, 1080};
    renderer.setSize(imageSize);

    //Creates scene
    auto scene{Scene::create()};

    //Orthographic camera
    float aspectRatio{16.0 / 9.0};
    float frustumSize{12};
    auto camera = OrthographicCamera::create(-frustumSize * aspectRatio / 2, frustumSize * aspectRatio / 2,
                                             frustumSize / 2, -frustumSize / 2, 0.1f, 1000);
    camera->position.z = 2;

    // Framebuffer (Help from GPT)
    std::vector<unsigned char> pixels(imageSize.first * imageSize.second * 3);

    //OPENCV Window
    std::string windowName{"ThreePP"};
    namedWindow(windowName, WINDOW_AUTOSIZE);

    //Resize event
    canvas.onWindowResize([&](WindowSize size) {
        // camera->aspect = size.aspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);

        imageSize = std::make_pair(size.width(), size.height());
        pixels.resize(imageSize.first * imageSize.second * 3);
    });

    //GeoGen class for generating "random geometries"
    GeoGen test(4, geoGen::Shape::CUBE, Color::aqua);
    GeoGen test2(4, geoGen::Shape::CUBE, Color::red);
    GeoGen test3(4, geoGen::Shape::CUBE, Color::green);
    test.generate();
    test2.generate();
    test3.generate();

    //Adds the generated geometries to the scene
    test.addToScene(scene);
    test2.addToScene(scene);
    test3.addToScene(scene);

    //Render loop
    Clock clock;
    canvas.animate([&]() {
        renderer.render(*scene, *camera);

        //Pixels are read into the buffer here.
        glReadPixels(0, 0, imageSize.first, imageSize.second, GL_BGR, GL_UNSIGNED_BYTE, pixels.data());

        //Creates an OPENCV Mat object for the pixels. (https://stackoverflow.com/questions/38489423/c-convert-rgb-1-d-array-to-opencv-mat-image)
        Mat image{imageSize.second, imageSize.first, CV_8UC3, pixels.data()};

        //OpenCV uses a different origin for the image, so it is flipped here.
        flip(image, image, 0);

        imshow(windowName, image);

        waitKey(1);
    });
}
