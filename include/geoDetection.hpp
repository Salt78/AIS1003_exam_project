#ifndef GEODETECTION_HPP
#define GEODETECTION_HPP

#include "detectedObjects.hpp"
#include "geoManipulator.hpp"
#include "gridManager.hpp"
#include "shapeColorHandler.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <threepp/threepp.hpp>
#include <utility>
#include <vector>


namespace geoDetectionNS {

    using namespace cv;
    using namespace threepp;
    using namespace shapeColorHandlerNS;
    using namespace geoManipulatorNS;

    class GeoDetection {
    private:
        std::string m_windowName{};
        std::pair<int, int> m_imageSize{};
        gridManagerNS::GridManager &m_grid;
        std::vector<unsigned char> m_pixels{};
        Mat m_mainCam{};
        Mat m_editedCam{};
        std::vector<DetectedObjects<Rect>> m_detectedObjects{};

        ShapeColorHandler m_colorProfiles{};
        GeoManipulator m_manipulator{m_colorProfiles, m_grid};


        void setupVirtualCam();


        void setContours(Mat &img, const Color::ColorName &color);


        void contourDetection(Color::ColorName color);

    public:
        GeoDetection(std::string windowName, std::pair<int, int> imageSize, gridManagerNS::GridManager &grid);

        void imageProcessing(bool showCam = true);
    };
}// namespace geoDetectionNS
#endif//GEODETECTION_HPP
