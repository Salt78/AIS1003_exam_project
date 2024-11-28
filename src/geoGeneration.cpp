#include "geoGeneration.hpp"
#include <random>


using namespace threepp;
using namespace shapeColorNS;
using namespace gridManagerNS;
using namespace geoGenNS;


// Random number generator https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
ShapeColorHandler::Shapes GeoGen::randomShape() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<std::vector<ShapeColorHandler::Shapes>::size_type> dist(0, ShapeColorHandler::getSupportedShapes().size() - 1);

    return ShapeColorHandler::getSupportedShapes()[dist(rd)];
}


Color::ColorName GeoGen::randomColor() const {
    // Random number generator https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<std::vector<Color::ColorName>::size_type> dist(0, shapeColorHandler.getSupportedColors().size() - 1);

    return shapeColorHandler.getColorIntBased(static_cast<int>(dist(rd)));
}


void GeoGen::addToScene() const {
    for (const auto &i: m_geoVec) {
        m_scene.add(i);

        //Optimises the raycasting process. (Tip from teacher)
        Box3 boundingBox{};//Adds a bounding box to the mesh.
        boundingBox.setFromObject(*i);
    }
}


void GeoGen::processMesh(const ShapeColorHandler::Shapes shape, std::shared_ptr<MeshBasicMaterial> &material) {
    switch (shape) {
        case ShapeColorHandler::Shapes::CUBE: {
            std::shared_ptr<BoxGeometry> cubeGeometry{};
            cubeGeometry = BoxGeometry::create(m_meshSize, m_meshSize, 0);

            createMesh(cubeGeometry, material);
            break;
        }
        case ShapeColorHandler::Shapes::CIRCLE: {
            std::shared_ptr<SphereGeometry> circleGeometry{};
            circleGeometry = SphereGeometry::create(m_meshSize / 2, 30, 20);

            createMesh(circleGeometry, material);
            break;
        }
        default:;
    }
}


GeoGen::GeoGen(Scene &scene, GridManager &grid, const float meshSize) : m_scene(scene), m_grid(grid), m_meshSize(meshSize) {}


void GeoGen::generateRND(const int quantity) {

    for (int i{}; i < quantity; i++) {
        const ShapeColorHandler::Shapes shape = randomShape();
        auto material = MeshBasicMaterial::create({{"color", randomColor()}});

        if (shape == ShapeColorHandler::Shapes::CIRCLE) {
            material->side = Side::Double;
        }

        processMesh(shape, material);
    }
    addToScene();
    m_geoVec.clear();
}