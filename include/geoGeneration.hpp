#ifndef SCENERY_HPP
#define SCENERY_HPP

#include "gridManager.hpp"
#include "shapeColorHandler.hpp"
#include "threepp/threepp.hpp"


namespace geoGenNS {
    using namespace threepp;
    using namespace gridManagerNS;
    using namespace shapeColorHandlerNS;

    class GeoGen {

    private:
        Scene &m_scene;
        GridManager &m_grid;
        const float m_meshSize{40};
        std::shared_ptr<MeshBasicMaterial> m_material{};
        int m_quantity{5};
        std::vector<std::shared_ptr<Mesh>> m_geoVec{};

        ShapeColorHandler shapeColorHandler{};


        template<typename T>
        void createMesh(std::shared_ptr<T> &geometry);

        void addToScene() {
            for (const auto &i: m_geoVec) {
                m_scene.add(i);

                Box3 boundingBox{};//Adds a bounding box to the mesh
                boundingBox.setFromObject(*i);
            }
        }


        void gengen(const ShapeColorHandler::Shapes shape) {
            switch (shape) {
                case ShapeColorHandler::Shapes::CUBE: {
                    std::shared_ptr<BoxGeometry> cubeGeometry{};
                    cubeGeometry = BoxGeometry::create(m_meshSize, m_meshSize, 0);

                    createMesh(cubeGeometry);
                    addToScene();
                    break;
                }
                case ShapeColorHandler::Shapes::CIRCLE: {
                    std::shared_ptr<SphereGeometry> circleGeometry{};
                    circleGeometry = SphereGeometry::create(m_meshSize / 2, 30, 20);

                    createMesh(circleGeometry);
                    addToScene();
                    break;
                }
                default:;
            }
        }

    public:
        GeoGen(Scene &scene, GridManager &grid)
            : m_scene(scene), m_grid(grid) {}


        void generate() {

            for (auto &i: ShapeColorHandler::getSupportedShapes()) {
                for (auto &j: shapeColorHandler.getSupportedColors()) {
                    auto material = MeshBasicMaterial::create();
                    material->color = j;
                    m_material = material;

                    gengen(i);

                    m_geoVec.clear();
                }
            }
        }
    };
}// namespace geoGenNS

#include "createMesh.tpp"


#endif//SCENERY_HPP
