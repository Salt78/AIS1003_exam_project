#ifndef GEODETECTION_HPP
#define GEODETECTION_HPP

#include <string>
#include <utility>
#include <vector>
#include <threepp/threepp.hpp>
#include <glad/glad.h>
#include <opencv2/opencv.hpp>

namespace GeoDetectionNS {
    using namespace cv;

    class GeoDetection {
    private:
        std::string m_windowName{};
        std::pair<int, int> m_imageSize{};
        std::vector<unsigned char> pixels{};

    public:
        GeoDetection(std::string windowName, std::pair<int, int> imageSize)
            : m_windowName(std::move(windowName)), m_imageSize(imageSize),
              pixels(imageSize.first * imageSize.second * 3) {
            namedWindow(m_windowName, WINDOW_AUTOSIZE);
        }

        void virtualCamera() {
            //Pixels are read into the buffer here.
            glReadPixels(0, 0, m_imageSize.first, m_imageSize.second, GL_BGR, GL_UNSIGNED_BYTE, pixels.data());

            //Creates an OPENCV Mat object for the pixels. (https://stackoverflow.com/questions/38489423/c-convert-rgb-1-d-array-to-opencv-mat-image)
            Mat threeppCam{m_imageSize.second, m_imageSize.first, CV_8UC3, pixels.data()};

            //OpenCV uses a different origin for the image, so it is flipped here.
            flip(threeppCam, threeppCam, 0);

            imshow(m_windowName, threeppCam);
        }
    };
}

#endif //GEODETECTION_HPP
