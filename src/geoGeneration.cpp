#include "geoGeneration.hpp"
#include <random>


using namespace threepp;
using namespace gridManagerNS;
using namespace geoGenNS;


// Random number generator https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
GeoGen::Shape GeoGen::randomShape() {
    const std::vector<Shape> supportedShapes = {Shape::CUBE, Shape::CIRCLE};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<std::vector<Shape>::size_type> dist(0, supportedShapes.size() - 1);

    return supportedShapes[dist(mt)];
}

// Random number generator https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
Color::ColorName GeoGen::randomColor() {
    const std::vector<Color::ColorName> supportedColors = {Color::red, Color::green, Color::aqua, Color::orange};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<std::vector<Color::ColorName>::size_type> dist(0, supportedColors.size() - 1);

    return supportedColors[dist(mt)];
}


void GeoGen::addToScene() const {
    for (const auto &i: m_geoVec) {
        m_scene.add(i);

        //Optimises the raycasting process. (Tip from teacher)
        Box3 boundingBox{};//Adds a bounding box to the mesh.
        boundingBox.setFromObject(*i);
    }
}


void GeoGen::processMesh(const Shape shape, std::shared_ptr<MeshBasicMaterial> &material) {
    switch (shape) {
        case Shape::CUBE: {
            std::shared_ptr<BoxGeometry> cubeGeometry{};
            cubeGeometry = BoxGeometry::create(m_meshSize, m_meshSize, 0);

            createMesh(cubeGeometry, material);
            break;
        }
        case Shape::CIRCLE: {
            std::shared_ptr<SphereGeometry> circleGeometry{};
            circleGeometry = SphereGeometry::create(m_meshSize / 2, 30, 20);

            createMesh(circleGeometry, material);
            break;
        }
        default:;
    }
}


void GeoGen::cleanUp() {
    for (auto &i: m_geoVec) {
        m_scene.remove(*i);
    }
    m_scene.children.clear();
    m_geoVec.clear();
    m_grid.resetUsedCoords();
}


GeoGen::GeoGen(Scene &scene, GridManager &grid, const int quantity)
    : m_scene(scene), m_grid(grid), m_quantity(quantity) {
    generateRND();
}


void GeoGen::generateRND() {
    cleanUp();

    if (m_quantity > m_grid.getCoordQuantity()) {
        m_quantity = m_grid.getCoordQuantity();
    }

    for (int i{}; i < m_quantity; i++) {
        const Shape shape = randomShape();
        auto material = MeshBasicMaterial::create({{"color", randomColor()}});

        if (shape == Shape::CIRCLE) {
            //GPT suggested this to fix issues with raycasting
            material->side = Side::Double;
        }

        processMesh(shape, material);
    }
    addToScene();
}