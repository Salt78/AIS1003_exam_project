#ifndef GEODETECTION_HPP
#define GEODETECTION_HPP

#include <string>
#include <utility>
#include <vector>
#include <threepp/threepp.hpp>
#include <glad/glad.h>
#include <opencv2/opencv.hpp>

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

        static Mat processImage(Mat &img) {
            // Used a YT video to get the idea of how to pre-process the image: https://www.youtube.com/watch?v=2FYm3GOonhk&t=7467s

            Mat imgBlur;
            GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);

            Mat imgCanny;
            Canny(imgBlur, imgCanny, 25, 75);
            const Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
            Mat imgDilate;
            dilate(imgCanny, imgDilate, kernel);

            return imgDilate;
        }

        void setContours(Mat &img) {
            std::vector<std::vector<Point> > contours;
            std::vector<Vec4i> hierarchy;
            findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

            std::vector<std::vector<Point> > conPoly{contours.size()};
            std::vector<Rect> boundRect{contours.size()};
            for (int i{}; i < contours.size(); i++) {
                double peri = arcLength(contours[i], true);
                approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
                drawContours(m_mainCam, conPoly, i, Scalar(255, 0, 255), 2);
                boundRect[i] = boundingRect(conPoly[i]);
                rectangle(m_mainCam, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 255), 2);
            }
        }

        void setupVirtualCam() {
            //Pixels are read into the buffer here.
            glReadPixels(0, 0, m_imageSize.first, m_imageSize.second, GL_BGR, GL_UNSIGNED_BYTE, m_pixels.data());

            //Creates an OPENCV Mat object for the pixels. (https://stackoverflow.com/questions/38489423/c-convert-rgb-1-d-array-to-opencv-mat-image)
            m_mainCam = Mat(m_imageSize.second, m_imageSize.first, CV_8UC3, m_pixels.data());

            //OpenCV uses a different origin for the image, so it is flipped here.
            flip(m_mainCam, m_mainCam, 0);
        }

    public:
        GeoDetection(std::string windowName, std::pair<int, int> imageSize)
            : m_windowName(std::move(windowName)), m_imageSize(imageSize),
              m_pixels(imageSize.first * imageSize.second * 3) {
            namedWindow(m_windowName, WINDOW_AUTOSIZE);
        }

        void imageProcessing(const bool showCam = true) {
            setupVirtualCam();
            colorDetection();

            if (showCam == true) {
                imshow(m_windowName, m_mainCam);
            }
        }

        void colorDetection() {
            Mat mainCamHSV{};
            cvtColor(m_mainCam, mainCamHSV, COLOR_BGR2HSV);
            Scalar greenLower(46, 0, 0);
            Scalar greenUpper(68, 255, 255);
            Mat greenMask{};
            inRange(mainCamHSV, greenLower, greenUpper, greenMask);

            setContours(greenMask);

        }
    };
}

#endif //GEODETECTION_HPP
