#ifndef GEOMANIPULATOR_HPP
#define GEOMANIPULATOR_HPP
#include "detectedObjects.hpp"
#include "gridManager.hpp"
#include "shapeColorHandler.hpp"
#include "threepp/threepp.hpp"
#include <vector>


namespace geoManipulatorNS {

    using namespace geoDetectionNS;
    using namespace threepp;
    using namespace gridManagerNS;
    using namespace shapeColorHandlerNS;


    class GeoManipulator {
    private:
        ShapeColorHandler &m_shapeColor;
        GridManager &m_grid;
        //Stores meshes that have been found in the scene
        std::vector<DetectedObjects<Mesh *>> m_meshObjects;
        bool m_hasBeenRun{false};

        //NEEDS COMMENT


        static Vector2 getCenterMesh(const DetectedObjects<Rect> &rectObject) {
            const Vector2 meshCenter{
                    (rectObject.getObject().tl().x + rectObject.getObject().br().x) / 2,
                    800 - ((rectObject.getObject().tl().y + rectObject.getObject().br().y) / 2)};
            return meshCenter;
        }

        void convertToMesh(std::vector<DetectedObjects<Rect>> &object3d) {

            //Did use some GPT to help me figure out how to convert from "Intersect" to "Mesh"
            Raycaster raycaster;
            for (const auto &i: object3d) {
                Vector2 ndc = {
                        (getCenterMesh(i).x / 800.0f) * 2.0f - 1.0f,// X normalized
                        (getCenterMesh(i).y / 800.0f) * 2.0f - 1.0f // Y normalized (already inverted in getCenterMesh)
                };

                raycaster.setFromCamera(ndc, *m_grid.getCamera());

                std::vector<Intersection> intersect = raycaster.intersectObjects(m_grid.getScene()->children, false);
                if (!intersect.empty()) {
                    auto objectPtr = intersect[0].object;
                    if (objectPtr) {
                        auto intersectedMesh = objectPtr->as<Mesh>();
                        if (intersectedMesh) {
                            m_meshObjects.emplace_back(intersectedMesh, i.getShape(), i.getColor());
                        }
                    }
                    //std::shared_ptr<Mesh> intersectedMesh = intersect[0].object->as<std::shared_ptr<Mesh>()>;
                }
            }
        }

        auto sortVector(ShapeColorHandler::Shapes shape, Color color) {
            std::vector<DetectedObjects<Mesh *>> sortedVec{};

            std::copy_if(m_meshObjects.begin(), m_meshObjects.end(), std::back_inserter(sortedVec),
                         [&](const DetectedObjects<Mesh *> &i) {
                             return i.getShape() == shape && i.getColor() == color;
                         });
            return sortedVec;
        }

        auto sortMeshes() {
            std::vector<DetectedObjects<Mesh *>> compSortedVec{};
            for (auto &j: m_shapeColor.getSupportedShapes()) {
                for (auto &i: m_shapeColor.getSupportedColors()) {
                    std::vector<DetectedObjects<Mesh *>> tempVec = sortVector(j, i);
                    compSortedVec.insert(compSortedVec.end(), tempVec.begin(), tempVec.end());
                }
            }
            return compSortedVec;
        }


    public:
        explicit GeoManipulator(ShapeColorHandler &shapeColorProfiles, GridManager &grid)
            : m_shapeColor(shapeColorProfiles), m_grid(grid) {
        }

        [[nodiscard]] bool hasBeenRun() const {
            return m_hasBeenRun;
        }
        void resetRunCounter() {
            m_hasBeenRun = false;
        }

        void reArrangeMeshes(std::vector<DetectedObjects<Rect>> &object3d) {
            convertToMesh(object3d);

            m_grid.resetScene();

            int key{1};
            std::vector<DetectedObjects<Mesh *>> arrangedMesh = sortMeshes();
            for (auto &i: arrangedMesh) {
                std::pair<float, float> coords = m_grid.getCoords(key);
                key++;

                i.getObject()->position.x = coords.first;
                i.getObject()->position.y = coords.second;
                i.getObject()->position.z = 0;
                m_grid.getScene()->add(std::shared_ptr<Object3D>(i.getObject()));
            }
            m_hasBeenRun = true;
        }
    };
}// namespace geoManipulatorNS


#endif//GEOMANIPULATOR_HPP
