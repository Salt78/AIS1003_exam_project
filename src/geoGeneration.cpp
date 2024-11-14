#include "geoGeneration.hpp"

using namespace geoGenNS;

GeoGen::GeoGen(float meshSize, int quantity, geoGenNS::Shape shape, Color::ColorName color)
    : m_meshSize{meshSize}, m_quantity{quantity}, m_shape{shape}, m_color{color} {
}

void GeoGen::addToScene(Scene &scene) {
    for (const auto &i: m_geoVec) {
        scene.add(i);

        Box3 boundingBox{}; //Adds a bounding box to the mesh
        boundingBox.setFromObject(*i);
    }
}

void GeoGen::generate(GridManager &grid) {
    m_material = MeshBasicMaterial::create();
    m_material->color = m_color;

    switch (m_shape) {
        case Shape::CUBE: {
            std::shared_ptr<BoxGeometry> cubeGeometry{};
            cubeGeometry = BoxGeometry::create(m_meshSize, m_meshSize, 0);

            createMesh(grid, cubeGeometry);
            addToScene(*grid.getScene());
            break;
        }
        case Shape::CAPSULE: {
            std::shared_ptr<CapsuleGeometry> capsuleGeometry{};
            capsuleGeometry = CapsuleGeometry::create(25, 50, 10, 20);

            createMesh(grid, capsuleGeometry);
            addToScene(*grid.getScene());
            break;
        }
        case Shape::CIRCLE: {
            std::shared_ptr<CircleGeometry> circleGeometry{};
            circleGeometry = CircleGeometry::create(m_meshSize / 2, 30, 0, 2 * std::numbers::pi);

            createMesh(grid, circleGeometry);
            addToScene(*grid.getScene());
            break;
        }
        case Shape::CYLINDER: {
            std::shared_ptr<CylinderGeometry> cylinderGeometry{};
            cylinderGeometry = CylinderGeometry::create(1, 1, 1);

            createMesh(grid, cylinderGeometry);
            addToScene(*grid.getScene());
            break;
        }
    }
}
