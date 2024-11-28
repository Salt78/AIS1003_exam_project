#ifndef GEOMANIPULATOR_HPP
#define GEOMANIPULATOR_HPP

#include <vector>
#include "threepp/threepp.hpp"
#include "detectedObjects.hpp"
#include "gridManager.hpp"
#include "shapeColorHandler.hpp"


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
        bool m_hasBeenRun{false};


        static threepp::Vector2 getCenterCoords(const DetectedObjects<cv::Rect> &rectObject);


        void emptyScene() const;


        void resetRunCounter();


        [[nodiscard]] auto convertToMesh(const std::vector<DetectedObjects<cv::Rect>> &object3d) const;


        static auto filterByShapeAndColor(std::vector<DetectedObjects<std::shared_ptr<threepp::Mesh>>> &meshObjects, shapeColorNS::ShapeColorHandler::Shapes shape, threepp::Color color);


        auto groupMeshesByShapeAndColor(std::vector<DetectedObjects<std::shared_ptr<threepp::Mesh>>> &meshObjects) const;


    public:
        explicit GeoManipulator(gridManagerNS::GridManager &grid, threepp::Scene &scene, threepp::Camera &camera);


        [[nodiscard]] bool hasBeenRun() const;


        void cleanUp();


        /**
         * Rearranges the given objects in the scene.
         * @param object3d Objects that are to be rearranged in the scene.
         */
        void reArrangeMeshes(const std::vector<DetectedObjects<cv::Rect>> &object3d);
    };
}// namespace geoManipulatorNS


#endif//GEOMANIPULATOR_HPP
