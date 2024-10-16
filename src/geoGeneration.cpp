#include "geoGeneration.hpp"

using namespace threepp;

namespace geoGen {
    enum class Shape {
        CUBE,
        SPHERE,
        CYLINDER,
        CONE
    };
}


class GeoGen {
private:
    //General properties
    std::string m_name{};
    Color::ColorName m_color{};
    int m_quantity{};
    geoGen::Shape m_shape{};

    std::shared_ptr<MeshBasicMaterial> m_material;

    std::vector<std::shared_ptr<Mesh> > m_geoVec{};

public:
    GeoGen(std::string name, int quantity = 0, geoGen::Shape shape = geoGen::Shape::CUBE)
        : m_name{std::move(name)}, m_quantity{quantity}, m_shape{shape} {
    }

    [[nodiscard]] std::string getName() const {
        return m_name;
    }

    [[nodiscard]] Color::ColorName getColor() const {
        return m_color;
    }

    [[nodiscard]] int getQuantity() const {
        return m_quantity;
    }

    [[nodiscard]] std::string getShape() const {
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

    void generate() {
        std::shared_ptr<MeshBasicMaterial> m_material{MeshBasicMaterial::create()};
        m_material->color = Color::green;

        int i{}; // for loop counter


        switch (m_shape) {
            case geoGen::Shape::CUBE: {
                std::shared_ptr<BoxGeometry> cubeGeometry{};
                cubeGeometry = BoxGeometry::create(1, 1, 1);

                for (i; i > m_quantity; i++) {
                    m_geoVec[i] = Mesh::create(cubeGeometry, m_material);
                    m_geoVec[i]->position.set(i, i, i);
                }

                break;
            }
            case geoGen::Shape::CONE: {
                std::shared_ptr<ConeGeometry> coneGeometry{};
                coneGeometry = ConeGeometry::create(1, 1, 1);

                for (i; i > m_quantity; i++) {
                    m_geoVec[i] = Mesh::create(coneGeometry, m_material);
                    m_geoVec[i]->position.set(i, i, i);
                }
                break;
            }
            case geoGen::Shape::SPHERE: {
                std::shared_ptr<SphereGeometry> sphereGeometry{};
                sphereGeometry = SphereGeometry::create(1, 1, 1);

                for (i; i > m_quantity; i++) {
                    m_geoVec[i] = Mesh::create(sphereGeometry, m_material);
                    m_geoVec[i]->position.set(i, i, i);
                }

                break;
            }
            case geoGen::Shape::CYLINDER: {
            }
                std::shared_ptr<CylinderGeometry> cylinderGeometry{};
                cylinderGeometry = CylinderGeometry::create(1, 1, 1);

                for (i; i > m_quantity; i++) {
                    m_geoVec[i] = Mesh::create(cylinderGeometry, m_material);
                    m_geoVec[i]->position.set(i, i, i);
                }
                break;
        }
    }
};
