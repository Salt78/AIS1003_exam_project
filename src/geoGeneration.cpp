#include "geoGeneration.hpp"


using namespace threepp;
using namespace gridManagerNS;
using namespace geoGenNS;


GeoGen::Shape GeoGen::randomShape() {
    static const std::vector<Shape> supportedShapes = {Shape::CUBE, Shape::CIRCLE};
    const int randNum = threepp::math::randInt(0, static_cast<int>(supportedShapes.size() - 1));

    return supportedShapes[randNum];
}

Color::ColorName GeoGen::randomColor() {
    const std::vector<Color::ColorName> supportedColors = {Color::red, Color::green, Color::aqua, Color::orange};
    const int randNum = threepp::math::randInt(0, static_cast<int>(supportedColors.size() - 1));

    return supportedColors[randNum];
}


void GeoGen::addToScene() const {
    for (const auto &mesh: m_geoVec) {
        m_scene.add(mesh);
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
            circleGeometry = SphereGeometry::create(m_meshSize / 2, 6, 6);

            createMesh(circleGeometry, material);
            break;
        }
        default:;
    }
}


void GeoGen::cleanUp() {
    for (auto &mesh: m_geoVec) {
        m_scene.remove(*mesh);
    }
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