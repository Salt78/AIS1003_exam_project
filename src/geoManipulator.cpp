#include "geoManipulator.hpp"
#include <stdexcept>

using namespace geoManipulatorNS;
using namespace shapeColorNS;
using namespace gridManagerNS;
using namespace threepp;
using namespace cv;


/**
 *
 * @param rectObject Rect object
 * @return Returns the center of the object
 */
Vector2 GeoManipulator::getCenterCoords(const DetectedObjects<Rect> &rectObject) {
    const Vector2 meshCenter{
            (rectObject.getObject().tl().x + rectObject.getObject().br().x) / 2,
            800 - ((rectObject.getObject().tl().y + rectObject.getObject().br().y) / 2)};
    return meshCenter;
}


void GeoManipulator::resetRunCounter() {
    m_hasBeenRun = false;
}


/**
 * @brief Uses a threepp::Raycaster to convert the Rect objects to Mesh objects.
 * @param object3d Vector of Rect objects
 * @return Vector of Mesh objects
 */
auto GeoManipulator::convertToMesh(const std::vector<DetectedObjects<Rect>> &object3d) const {

    //Did use some GPT to help me figure out how to convert from "Intersect" to "Mesh"
    Raycaster raycaster;
    std::vector<DetectedObjects<Mesh *>> meshObjects{};
    for (const auto &i: object3d) {
        //GPT told me that I needed to normalize the coordinates.
        Vector2 ndc = {
                (getCenterCoords(i).x / 800.0f) * 2.0f - 1.0f,// X normalized
                (getCenterCoords(i).y / 800.0f) * 2.0f - 1.0f // Y normalized (already inverted in getCenterMesh)
        };

        raycaster.setFromCamera(ndc, m_camera);

        //Lent this code from a Threepp example.
        std::vector<Intersection> intersect = raycaster.intersectObjects(m_scene.children, false);
        if (intersect.empty()) {
            throw std::logic_error("No intersection found");
        }
        const auto objectPtr = intersect[0].object;
        if (!objectPtr) {
            throw std::logic_error("No Object3D found");
        }
        const auto intersectedMesh = objectPtr->as<Mesh>();
        if (!intersectedMesh) {
            throw std::logic_error("No Mesh found");
        }
        //GPT code for cloning the raw Mesh object into a std::shared_ptr<Mesh>
        meshObjects.emplace_back(intersectedMesh, i.getShape(), i.getColor());
    }
    return meshObjects;
}


/**
 * @brief Filters the Mesh objects based on the desired shape and color.
 * @param meshObjects Vector of Mesh objects
 * @param shape Desired shape
 * @param color Desired color
 * @return Vector of Mesh objects that match the desired shape and color
 */
auto GeoManipulator::filterByShapeAndColor(std::vector<DetectedObjects<Mesh *>> &meshObjects, const ShapeColorHandler::Shapes shape, const Color color) {
    std::vector<DetectedObjects<Mesh *>> sortedVec{};

    //Used a GPT to help me figure out how to sort the vector based on shape and color.
    std::ranges::copy_if(meshObjects, std::back_inserter(sortedVec),
                         [&](const DetectedObjects<Mesh *> &i) {
                             return i.getShape() == shape && i.getColor() == color;
                         });
    return sortedVec;
}


/**
 * @brief Final step in the rearrangement process. Groups the Mesh objects by shape and color.
 * @param meshObjects Vector of Mesh objects
 * @return Vector of Mesh objects grouped by shape and color
 */
auto GeoManipulator::groupMeshesByShapeAndColor(std::vector<DetectedObjects<Mesh *>> &meshObjects) const {
    std::vector<DetectedObjects<Mesh *>> compSortedVec{};

    for (auto &j: ShapeColorHandler::getSupportedShapes()) {
        for (auto &i: m_shapeColor.getSupportedColors()) {
            std::vector<DetectedObjects<Mesh *>> tempVec = filterByShapeAndColor(meshObjects, j, i);
            compSortedVec.insert(compSortedVec.end(), tempVec.begin(), tempVec.end());
        }
    }
    return compSortedVec;
}


GeoManipulator::GeoManipulator(GridManager &grid, Scene &scene, Camera &camera)
    : m_grid(grid), m_scene(scene), m_camera(camera) {
}


bool GeoManipulator::hasBeenRun() const {
    return m_hasBeenRun;
}


void GeoManipulator::reArrangeMeshes(const std::vector<DetectedObjects<Rect>> &object3d) {
    if (!m_hasBeenRun) {
        std::vector<DetectedObjects<Mesh*>> meshObjects{};
        try {
            meshObjects = convertToMesh(object3d);
        } catch (const std::logic_error &) {
            return;
        }

        int key{1};
        const std::vector<DetectedObjects<Mesh *>> arrangedMesh = groupMeshesByShapeAndColor(meshObjects);
        for (auto &i: arrangedMesh) {
            const std::pair<float, float> coords = m_grid.getCoords(key);
            key++;

            i.getObject()->position.x = coords.first;
            i.getObject()->position.y = coords.second;
            i.getObject()->position.z = 0;
        }
        m_hasBeenRun = true;
    }
}
