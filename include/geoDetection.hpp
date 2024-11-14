#ifndef GEODETECTION_HPP
#define GEODETECTION_HPP

#include <string>
#include <utility>
#include <vector>
#include <threepp/threepp.hpp>
#include <opencv2/opencv.hpp>
#include "detectedObjects.hpp"

namespace geoDetectionNS {
    using namespace cv;
    using namespace threepp;


    class GeoDetection {
    private:
        std::string m_windowName{};
        std::pair<int, int> m_imageSize{};
        std::vector<unsigned char> m_pixels{};
        Mat m_mainCam{};
        Mat m_editedCam{};
        std::vector<DetectedObjects<Rect> > m_detectedObjects{};


        const std::map<Color::ColorName, std::pair<Scalar, Scalar> > colorProfiles = {
            {Color::green, std::pair<Scalar, Scalar>(Scalar(46, 0, 0), Scalar(68, 255, 255))},
            {Color::aqua, std::pair<Scalar, Scalar>(Scalar(76, 0, 0), Scalar(90, 255, 255))},
            {Color::orange, std::pair<Scalar, Scalar>(Scalar(13, 0, 0), Scalar(32, 255, 255))},
            {Color::red, std::pair<Scalar, Scalar>(Scalar(0, 32, 0), Scalar(0, 255, 255))}
        };


        void setupVirtualCam();


        void setContours(Mat &img, const Color::ColorName &color);


        void contourDetection(Color::ColorName color);

    public:
        GeoDetection(std::string windowName, std::pair<int, int> imageSize);


        void imageProcessing(bool showCam = true);
    };
}
#endif //GEODETECTION_HPP
