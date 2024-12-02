#ifndef GEOMANIPULATOR_HPP
#define GEOMANIPULATOR_HPP

#include "detectedObjects.hpp"
#include "gridManager.hpp"
#include "shapeColorHandler.hpp"
#include "threepp/threepp.hpp"
#include <vector>


namespace geoManipulatorNS {


    /**
     * Manages the rearrangement of objects in the scene.
     *
     * */
    class GeoManipulator {

    private:
        gridManagerNS::GridManager &m_grid;
        threepp::Scene &m_scene;
        threepp::Camera &m_camera;
        shapeColorNS::ShapeColorHandler m_shapeColor{};

        std::vector<DetectedObjects<threepp::Mesh *>> m_meshObjs;
        std::vector<DetectedObjects<threepp::Mesh *>> m_meshObjsSorted;


        [[nodiscard]] threepp::Vector2 getCenterCoords(const DetectedObjects<cv::Rect> &rectObject) const;

        [[nodiscard]] threepp::Vector2 getNDC(threepp::Vector2 coords) const;

        void convertToMesh(const std::vector<DetectedObjects<cv::Rect>> &rectObjects);

        static std::vector<DetectedObjects<threepp::Mesh *>>
        filterByShapeAndColor(std::vector<DetectedObjects<threepp::Mesh *>> &meshObjects, shapeColorNS::ShapeColorHandler::Shapes shape, threepp::Color color);

        void groupMeshesByShapeAndColor();

    public:
        explicit GeoManipulator(gridManagerNS::GridManager &grid, threepp::Scene &scene, threepp::Camera &camera);

        /**
         * Rearranges the given objects in the scene.
         * @param rectObjects Objects that are to be rearranged in the scene.
         */
        void reArrangeMeshes(const std::vector<DetectedObjects<cv::Rect>> &rectObjects);
    };
}// namespace geoManipulatorNS


#endif//GEOMANIPULATOR_HPP
