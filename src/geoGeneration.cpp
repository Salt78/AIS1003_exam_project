#include "geoGeneration.hpp"

GeoGen::GeoGen(int quantity, geoGen::Shape shape, Color::ColorName color)
    : m_quantity{quantity}, m_shape{shape}, m_color{color} {
}


Color::ColorName GeoGen::getColor() const {
    return m_color;
}

int GeoGen::getQuantity() const {
    return m_quantity;
}

std::string GeoGen::getShape() const {
    switch (m_shape) {
        case geoGen::Shape::CUBE:
            return "cube";
        case geoGen::Shape::CAPSULE:
            return "cone";
        case geoGen::Shape::CIRCLE:
            return "sphere";
        case geoGen::Shape::CYLINDER:
            return "cylinder";
    }
    return "unknown";
}

std::vector<std::shared_ptr<Mesh> > GeoGen::getGeoVec() const {
    return m_geoVec;
}

void GeoGen::addToScene(Scene &scene) {
    for (int i{}; i < m_geoVec.size(); i++) {
        scene.add(m_geoVec[i]);
    }
}

void GeoGen::generate(GridManager &grid, Scene &scene) {
    m_material = MeshBasicMaterial::create();
    m_material->color = m_color;


    switch (m_shape) {
        case geoGen::Shape::CUBE: {
            std::shared_ptr<BoxGeometry> cubeGeometry{};
            cubeGeometry = BoxGeometry::create(40, 40, 0);

            createMesh(grid, cubeGeometry);
            addToScene(scene);
            break;
        }
        case geoGen::Shape::CAPSULE: {
            std::shared_ptr<CapsuleGeometry> capsuleGeometry{};
            capsuleGeometry = CapsuleGeometry::create(25, 50, 10, 20);

            createMesh(grid, capsuleGeometry);
            addToScene(scene);
            break;
        }
        case geoGen::Shape::CIRCLE: {
            std::shared_ptr<CircleGeometry> circleGeometry{};
            circleGeometry = CircleGeometry::create(20, 30, 0, 2 * std::numbers::pi);

            createMesh(grid, circleGeometry);
            addToScene(scene);
            break;
        }
        case geoGen::Shape::CYLINDER: {
            std::shared_ptr<CylinderGeometry> cylinderGeometry{};
            cylinderGeometry = CylinderGeometry::create(1, 1, 1);

            createMesh(grid, cylinderGeometry);
            addToScene(scene);
            break;
        }
    }
}
