#include <opencv2/opencv.hpp>
#include <iostream>
#include "threepp/threepp.hpp"

using namespace threepp;

int main() {
    Canvas canvas("RandomGeometry", {{"aa", 4}});

    GLRenderer renderer(canvas.size());


    auto scene{Scene::create()};

    //Camera and orbitial controls

    auto camera{PerspectiveCamera::create(75, 800.0f / 600.0f, 0.1f, 1000.0f)};
    camera->position.z = 5;

    OrbitControls controls(*camera, canvas);

    //Random geometry for testing

    auto geometry{BoxGeometry::create(1, 1, 1)};
    auto material{MeshBasicMaterial::create()};
    material->color = Color::yellow;

    auto cube{Mesh::create(geometry, material)};

    scene->add(cube);

    Clock clock;
    canvas.animate([&]() {
        renderer.render(*scene, *camera);
    });
}
