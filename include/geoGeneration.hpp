#ifndef SCENERY_HPP
#define SCENERY_HPP

#include "gridManager.hpp"
#include "shapeColorHandler.hpp"
#include "threepp/threepp.hpp"
#include <random>


namespace geoGenNS {
    using namespace threepp;
    using namespace gridManagerNS;
    using namespace shapeColorHandlerNS;

    class GeoGen {

    private:
        Scene &m_scene;
        GridManager &m_grid;
        float m_meshSize{};
        int m_quantity{};
        std::vector<std::shared_ptr<Mesh>> m_geoVec{};

        ShapeColorHandler shapeColorHandler{};


        template<typename T>
        void createMesh(std::shared_ptr<T> &geometry, std::shared_ptr<MeshBasicMaterial> &material);

        ShapeColorHandler::Shapes randomShape() {
            // Random number generator https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(0, shapeColorHandler.getSupportedShapes().size() - 1);

            return shapeColorHandler.getSupportedShapes()[dist(rd)];
        }


        Color::ColorName randomColor() {
            // Random number generator https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(0, shapeColorHandler.getSupportedColors().size() - 1);

            return shapeColorHandler.getColorIntBased(dist(rd));
        }


        void addToScene() {
            for (const auto &i: m_geoVec) {
                m_scene.add(i);

                Box3 boundingBox{};//Adds a bounding box to the mesh
                boundingBox.setFromObject(*i);
            }
        }


        void processMesh(const ShapeColorHandler::Shapes shape, std::shared_ptr<MeshBasicMaterial> &material) {
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

    public:
        GeoGen(Scene &scene, GridManager &grid, const float meshSize = 40)
            : m_scene(scene), m_grid(grid), m_meshSize(meshSize) {}


        void generateRND(int quantity = 30) {

            for (int i{}; i < quantity; i++) {
                ShapeColorHandler::Shapes shape = randomShape();
                auto material = MeshBasicMaterial::create({{"color", randomColor()}});

                if (shape == ShapeColorHandler::Shapes::CIRCLE) {
                    material->side = Side::Double;
                }

                processMesh(shape, material);
            }
            addToScene();
            m_geoVec.clear();
        }
    };
}// namespace geoGenNS

#include "createMesh.tpp"


#endif//SCENERY_HPP
