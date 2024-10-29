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

void GeoGen::generate() {
    std::shared_ptr<MeshBasicMaterial> m_material{MeshBasicMaterial::create()};
    m_material->color = m_color;

    // Random number generator https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(50, 800);


    switch (m_shape) {
        case geoGen::Shape::CUBE: {
            std::shared_ptr<BoxGeometry> cubeGeometry{};
            cubeGeometry = BoxGeometry::create(50, 50, 0);

            for (int i{}; i < m_quantity; i++) {
                m_geoVec.push_back(Mesh::create(cubeGeometry, m_material));
                m_geoVec[i]->position.set(dist(rd), dist(rd), 0);
            }

            break;
        }
        case geoGen::Shape::CAPSULE: {
            std::shared_ptr<CapsuleGeometry> capsuleGeometry{};
            capsuleGeometry = CapsuleGeometry::create(25, 50, 10, 20);

            for (int o{}; o < m_quantity; o++) {
                m_geoVec.push_back(Mesh::create(capsuleGeometry, m_material));
                m_geoVec[o]->position.set(dist(rd), dist(rd), 0);
            }
            break;
        }
        case geoGen::Shape::CIRCLE: {
            std::shared_ptr<CircleGeometry> circleGeometry{};
            circleGeometry = CircleGeometry::create(25, 30, 0, 2 * std::numbers::pi);

            for (int z{}; z < m_quantity; z++) {
                m_geoVec.push_back(Mesh::create(circleGeometry, m_material));
                m_geoVec[z]->position.set(dist(rd), dist(rd), 1);
                m_geoVec[z]->rotation.x = std::numbers::pi;
            }

            break;
        }
        case geoGen::Shape::CYLINDER: {
        }
            std::shared_ptr<CylinderGeometry> cylinderGeometry{};
            cylinderGeometry = CylinderGeometry::create(1, 1, 1);

            for (int x{}; x < m_quantity; x++) {
                m_geoVec.push_back(Mesh::create(cylinderGeometry, m_material));
                m_geoVec[x]->position.set(dist(rd), dist(rd), 0);
            }
            break;
    }
}

void GeoGen::addToScene(const std::shared_ptr<Scene> &scene) {
    for (int i{}; i < m_geoVec.size(); i++) {
        scene->add(m_geoVec[i]);
    }
}
