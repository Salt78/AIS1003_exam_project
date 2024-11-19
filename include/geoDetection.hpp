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
        //Constructor properties
        std::string m_windowName{};
        std::pair<int, int> m_imageSize{};

        //For detection logic
        std::vector<unsigned char> m_pixels{};
        Mat m_mainCam{};
        Mat m_editedCam{};
        std::vector<DetectedObjects<Rect>> m_detectedObjects{};

        //Misc
        ShapeColorHandler m_colorProfiles{};

        void setupVirtualCam();


        void setContours(Mat &img, const Color::ColorName &color);


        void contourDetection(const std::vector<Color::ColorName> &color);

    public:
        GeoDetection(std::string windowName, std::pair<int, int> imageSize);

        void imageProcessing(bool showCam = true);

        [[nodiscard]] std::vector<DetectedObjects<Rect>> &getDetectedObjects() {
            return m_detectedObjects;
        }
    };
}// namespace geoDetectionNS
#endif//GEODETECTION_HPP
