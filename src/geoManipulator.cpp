#include "geoManipulator.hpp"
#include <stdexcept>

using namespace geoManipulatorNS;
using namespace shapeColorNS;
using namespace gridManagerNS;
using namespace threepp;
using namespace cv;

using rawMeshVec = std::vector<DetectedObjects<threepp::Mesh *>>;


/**
 *Nb: also flips the y-axis to accommodate the different coordinate system used by OpenCV.
 * @param rectObject Rect object
 * @return Returns the center of the object
 */
Vector2 GeoManipulator::getCenterCoords(const DetectedObjects<Rect> &rectObject) const {
    const Vector2 meshCenter{
            (rectObject.getObject().tl().x + rectObject.getObject().br().x) / 2,
            m_grid.getImgSize().first - ((rectObject.getObject().tl().y + rectObject.getObject().br().y) / 2)};
    return meshCenter;
}


/**
 * 
 * @param coords Cartesian coords
 * @return normalized device coordinates
 */ //GPT helped me with NDC conversion.
Vector2 GeoManipulator::getNDC(const Vector2 coords) const {
    const std::pair<int, int> imageSize = m_grid.getImgSize();
    const Vector2 ndc = {
            (coords.x / static_cast<float>(imageSize.first)) * 2.0f - 1.0f,
            (coords.y / static_cast<float>(imageSize.second)) * 2.0f - 1.0f};

    return ndc;
}

/**
 * @brief Uses a threepp::Raycaster to convert the Rect objects to Mesh objects.
 * @param rectObjects Vector of Rect objects
 * @return Vector of Mesh* objects
 */
 rawMeshVec GeoManipulator::convertToMesh(const std::vector<DetectedObjects<Rect>> &rectObjects) const {
    Raycaster raycaster;
    rawMeshVec meshObjects{};
    for (const auto &rect: rectObjects) {
        const Vector2 centerCoords = getCenterCoords(rect);
        const Vector2 ndc = getNDC(centerCoords);

        raycaster.setFromCamera(ndc, m_camera);

        //Lent this code from a Threepp example.
        std::vector<Intersection> intersect = raycaster.intersectObjects(m_scene.children, false);
        if (intersect.empty()) {
            throw std::logic_error("No intersection found");
        }
        auto *const objectPtr = intersect[0].object;
        if (!objectPtr) {
            throw std::logic_error("No object found");
        }
        auto *const intersectedMesh = objectPtr->as<Mesh>();
        if (!intersectedMesh) {
            throw std::logic_error("No mesh found");
        }
        meshObjects.emplace_back(intersectedMesh, rect.getShape(), rect.getColor());
    }
    return meshObjects;
}


/**
 * @brief Filters the Mesh objects based on the desired shape and color.
 * @param meshObjects Vector of Mesh objects
 * @param shape Desired shape
 * @param color Desired color
 * @return Vector of Mesh* objects that match the desired shape and color
 */
rawMeshVec GeoManipulator::filterByShapeAndColor(std::vector<DetectedObjects<Mesh *>> &meshObjects, const ShapeColorHandler::Shapes shape, const Color color) {
    std::vector<DetectedObjects<Mesh *>> sortedVec{};

    //Used a GPT to help me figure out how to sort the vector based on shape and color.
    std::ranges::copy_if(meshObjects, std::back_inserter(sortedVec),
                         [&](const DetectedObjects<Mesh *> &mesh) {
                             return mesh.getShape() == shape && mesh.getColor() == color;
                         });
    return sortedVec;
}


/**
 * @brief Final step in the rearrangement process. Groups the Mesh objects by shape and color.
 * @param meshObjects Vector of Mesh objects
 * @return Vector of Mesh* objects grouped by shape and color
 */
rawMeshVec GeoManipulator::groupMeshesByShapeAndColor(rawMeshVec &meshObjects) const {
    std::vector<DetectedObjects<Mesh *>> compSortedVec{};

    for (auto &color: m_shapeColor.getSupportedColors()) {
        for (auto &shape: ShapeColorHandler::getSupportedShapes()) {
            rawMeshVec tempVec = filterByShapeAndColor(meshObjects, shape, color);
            compSortedVec.insert(compSortedVec.end(), tempVec.begin(), tempVec.end());
        }
    }
    return compSortedVec;
}


GeoManipulator::GeoManipulator(GridManager &grid, Scene &scene, Camera &camera)
    : m_grid(grid), m_scene(scene), m_camera(camera) {
}


void GeoManipulator::reArrangeMeshes(const std::vector<DetectedObjects<Rect>> &rectObjects) const {
    rawMeshVec meshObjects{};
    try {
        meshObjects = convertToMesh(rectObjects);
    } catch (const std::logic_error &) {
        return;
    }

    int key{1};
    const rawMeshVec arrangedMesh = groupMeshesByShapeAndColor(meshObjects);
    for (auto &mesh: arrangedMesh) {
        const std::pair<float, float> coords = m_grid.getCoords(key);
        key++;

        mesh.getObject()->position.x = coords.first;
        mesh.getObject()->position.y = coords.second;
        mesh.getObject()->position.z = 0;
    }
}
