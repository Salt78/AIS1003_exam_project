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




        void setContours(Mat &img, const Color::ColorName &color);

    public:
        GeoDetection(std::string windowName, std::pair<int, int> imageSize);

        void contourDetection();

        void setupVirtualCam(GLRenderer &renderer);

        void imageProcessing(bool showCam);;

        [[nodiscard]] std::vector<DetectedObjects<Rect>> &getDetectedObjects() {
            return m_detectedObjects;
        }
        void cleanUp() {
            m_detectedObjects.clear();
        }

        void previewDetection() {
           contourDetection();
            cleanUp();
        }
    };
}// namespace geoDetectionNS
#endif//GEODETECTION_HPP
