#include <opencv2/opencv.hpp>
#include <iostream>

#include "../cmake-build-debug/_deps/threepp-src/src/external/glad/glad/glad.h"
#include "threepp/threepp.hpp"

using namespace threepp;
using namespace cv;

int main(int argc, char **argv) {
    Canvas canvas("RandomGeometry", {{"aa", 4}});

    GLRenderer renderer(canvas.size());
    std::pair<int, int> imageSize{1920, 1080};
    renderer.setSize(imageSize);


    auto scene{Scene::create()};

    //Camera and orbital controls

    auto camera{PerspectiveCamera::create(75, 800.0f / 600.0f, 0.1f, 1000.0f)};
    camera->position.z = 5;

    // Framebuffer (Help from GPT)
    std::vector<unsigned char> pixels(imageSize.first * imageSize.second * 3);

    //glPixelStorei(GL_PACK_ALIGNMENT, 1);

    // Choose the first pixels that are too be read into the buffer.
    const int x{0};
    const int y{0};

    //OPENCV Window

    std::string windowName{"ThreePP"};
    namedWindow(windowName, WINDOW_AUTOSIZE);


    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.aspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);

        imageSize = std::make_pair(size.width(), size.height());
        pixels.resize(imageSize.first * imageSize.second * 3);
    });


    OrbitControls controls(*camera, canvas);

    //Random geometry for testing

    auto geometry{BoxGeometry::create(1, 1, 1)};
    auto material{MeshBasicMaterial::create()};
    material->color = Color::yellow;

    auto cube{Mesh::create(geometry, material)};

    scene->add(cube);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);


    Clock clock;
    canvas.animate([&]() {
        renderer.render(*scene, *camera);

        //Pixels are read into the buffer here.
        glReadPixels(x, y, imageSize.first, imageSize.second, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());


        //Creates an OPENCV Mat object for the pixels. (https://stackoverflow.com/questions/38489423/c-convert-rgb-1-d-array-to-opencv-mat-image)
        Mat image{imageSize.first, imageSize.second, CV_8UC3, pixels.data()};
        cvtColor(image, image, cv::COLOR_RGB2BGR);
        flip(image, image, 0);


        imshow(windowName, image);

        waitKey(1);
    });
}
