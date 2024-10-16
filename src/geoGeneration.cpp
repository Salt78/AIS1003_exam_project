#include "geoGeneration.hpp"

GeoGen::GeoGen(int quantity, geoGen::Shape shape): m_quantity{quantity}, m_shape{shape} {
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
        case geoGen::Shape::CONE:
            return "cone";
        case geoGen::Shape::SPHERE:
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
    m_material->color = Color::green;

    int i{}; // for loop counter


    switch (m_shape) {
        case geoGen::Shape::CUBE: {
            std::shared_ptr<BoxGeometry> cubeGeometry{};
            cubeGeometry = BoxGeometry::create(1, 1, 1);

            for (i; i < m_quantity; i++) {
                m_geoVec.push_back(Mesh::create(cubeGeometry, m_material));
                m_geoVec[i]->position.set(i, i, i);
            }

            break;
        }
        case geoGen::Shape::CONE: {
            std::shared_ptr<ConeGeometry> coneGeometry{};
            coneGeometry = ConeGeometry::create(1, 1, 1);

            for (i; i < m_quantity; i++) {
                m_geoVec.push_back(Mesh::create(coneGeometry, m_material));
                m_geoVec[i]->position.set(i, i, i);
            }
            break;
        }
        case geoGen::Shape::SPHERE: {
            std::shared_ptr<SphereGeometry> sphereGeometry{};
            sphereGeometry = SphereGeometry::create(1, 1, 1);

            for (i; i < m_quantity; i++) {
                m_geoVec.push_back(Mesh::create(sphereGeometry, m_material));
                m_geoVec[i]->position.set(i, i, i);
            }

            break;
        }
        case geoGen::Shape::CYLINDER: {
        }
            std::shared_ptr<CylinderGeometry> cylinderGeometry{};
            cylinderGeometry = CylinderGeometry::create(1, 1, 1);

            for (i; i < m_quantity; i++) {
                m_geoVec.push_back(Mesh::create(cylinderGeometry, m_material));
                m_geoVec[i]->position.set(i, i, i);
            }
            break;
    }
}
