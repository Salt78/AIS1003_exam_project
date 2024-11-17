#ifndef GEOMANIPULATOR_HPP
#define GEOMANIPULATOR_HPP
#include "detectedObjects.hpp"
#include "enum_Shape.hpp"
#include "gridManager.hpp"
#include "threepp/threepp.hpp"
#include <geoDetection.hpp>
#include <vector>

namespace geoManipulatorNS {
    using namespace geoDetectionNS;
    using namespace threepp;
    using namespace gridManagerNS;

    class GeoManipulator {
    private:
        GeoDetection &m_detector;
        GridManager &m_grid;
        std::shared_ptr<Camera> m_camera;
        //Stores meshes that have been found in the scene
        std::vector<DetectedObjects<std::shared_ptr<Mesh>>> m_meshObjects;
        std::vector<Shapes> m_supportedShapes{};

        //NEEDS COMMENT
        void getSupportedShapes() {
            std::vector<Shapes> supportedShapes{};
            for (int i{}; i < static_cast<int>(Shapes::ENDOFENUM); i++) {
                supportedShapes.push_back(static_cast<Shapes>(i));
            }
            m_supportedShapes = supportedShapes;
        }


        static Vector2 getCenterMesh(const DetectedObjects<Rect> &rectObject) {
            const Vector2 meshCenter{
                    (rectObject.getObject().tl().x + rectObject.getObject().br().x) / 2,
                    (rectObject.getObject().tl().y + rectObject.getObject().br().y) / 2};
            return meshCenter;
        }

        void getMeshes(const std::vector<DetectedObjects<Rect>> &rectObjects) {
            //Creates a mesh for the intersection test
            const auto geometry = BoxGeometry::create(10, 10, 50);
            const auto material = MeshBasicMaterial::create();
            const auto mesh = Mesh::create(geometry, material);


            //Did use some GPT to help me figure out how to convert from "Intersect" to "Mesh"
            Raycaster raycaster;
            for (const auto &i: rectObjects) {
                raycaster.setFromCamera(getCenterMesh(i), *m_camera);

                std::vector<Intersection> intersect{};
                if (!intersect.empty()) {
                    std::shared_ptr<Object3D> objectPtr(intersect[0].object, [](Object3D *) {
                    });
                    std::shared_ptr<Mesh> intersectedMesh = std::dynamic_pointer_cast<Mesh>(objectPtr);
                    m_meshObjects.emplace_back(intersectedMesh, i.getShape(), i.getColor());
                }
                //std::shared_ptr<Mesh> intersectedMesh = intersect[0].object->as<std::shared_ptr<Mesh>()>;
            }
        }

        auto sortVector(Shapes shape, Color color) {
            std::vector<DetectedObjects<std::shared_ptr<Mesh>>> sortedVec{};

            std::copy_if(m_meshObjects.begin(), m_meshObjects.end(), std::back_inserter(sortedVec),
                         [&](const DetectedObjects<std::shared_ptr<Mesh>> &i) {
                             return i.getShape() == shape && i.getColor() == color;
                         });
            return sortedVec;
        }

        auto sortMeshes() {
            std::vector<DetectedObjects<std::shared_ptr<Mesh>>> compSortedVec{};
            for (auto &j: m_supportedShapes) {
                for (auto &i: m_detector.getSupportedColors()) {
                    std::vector<DetectedObjects<std::shared_ptr<Mesh>>> tempVec = sortVector(j, i);
                    compSortedVec.insert(compSortedVec.end(), tempVec.begin(), tempVec.end());
                }
            }
            return compSortedVec;
        }


    public:
        explicit GeoManipulator(GeoDetection &detector, GridManager &grid, Camera &camera) : m_detector(detector), m_grid(grid), m_camera(&camera) {
            getSupportedShapes();
        }

        void reArrangeMeshes() {
            m_grid.resetScene();
            int key{1};
            std::vector<DetectedObjects<std::shared_ptr<Mesh>>> arrangedMesh = sortMeshes();
            ;
            for (auto &i: arrangedMesh) {
                std::pair<float, float> coords = m_grid.getCoords(key);
                key++;

                i.getObject()->position.x = coords.first;
                i.getObject()->position.y = coords.second;
                i.getObject()->position.z = 0;
                m_grid.getScene()->add(i.getObject());
            }
        }
    };
}// namespace geoManipulatorNS


#endif//GEOMANIPULATOR_HPP
