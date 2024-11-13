#ifndef GEOMANIPULATOR_HPP
#define GEOMANIPULATOR_HPP
#include <vector>
#include "DetectedObjects.hpp"
#include "threepp/threepp.hpp"
#include "gridManager.hpp"

namespace geoManipulatorNS {
    using namespace geoDetectionNS;
    using namespace threepp;
    using namespace gridManagerNS;

    class GeoManipulator {
    private:
        GridManager m_grid;
        std::vector<DetectedObjects<std::shared_ptr<Mesh> > > m_meshObjects;
        std::shared_ptr<Camera> m_camera;


        static Vector2 getCenterMesh(const DetectedObjects<Rect> &rectObject) {
            const Vector2 meshCenter{
                (rectObject.getObject().tl().x + rectObject.getObject().br().x) / 2,
                (rectObject.getObject().tl().y + rectObject.getObject().br().y) / 2
            };
            return meshCenter;
        }

        void getMeshes(const std::vector<DetectedObjects<Rect> > &rectObjects) {
            //Creates a mesh for the intersection test
            const auto geometry = BoxGeometry::create(10, 10, 50);
            const auto material = MeshBasicMaterial::create();
            const auto mesh = Mesh::create(geometry, material);


            //Did use some GPT to help me figure out how to convert from "Intersect" to "Mesh"
            Raycaster raycaster;
            for (const auto &i: rectObjects) {
                raycaster.setFromCamera(getCenterMesh(i), *m_camera);

                std::vector<Intersection> intersect{};
                intersect = raycaster.intersectObject(*mesh, false);
                //Extracts the mesh from the intersection
                auto intersectedMesh = intersect[0].object->as<Mesh>();
                std::shared_ptr<Mesh> intersectedMeshPtr(intersectedMesh);
                m_meshObjects.emplace_back(intersectedMeshPtr, i.getShape(), i.getColor());
            }
        }

    public:
        explicit GeoManipulator(GridManager &grid, Camera &camera): m_grid(grid), m_camera(&camera) {
        }

        /*void setup(const std::vector<DetectedObjects> &objects) {
        }*/
    };
}


#endif //GEOMANIPULATOR_HPP
