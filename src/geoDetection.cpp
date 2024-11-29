#include "geoDetection.hpp"
#include "shapeColorHandler.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace threepp;
using namespace geoDetectionNS;
using namespace shapeColorNS;


void GeoDetection::setupVirtualCam(GLRenderer &renderer) {
    //Pixels are read into the buffer here.
    renderer.readPixels({0, 0}, m_imageSize, Format::RGB, m_pixels.data());

    //Creates an OPENCV Mat object for the pixels. (https://stackoverflow.com/questions/38489423/c-convert-rgb-1-d-array-to-opencv-mat-image)
    Mat mainCam_RGB = Mat(m_imageSize.second, m_imageSize.first, CV_8UC3, m_pixels.data());
    cvtColor(mainCam_RGB, m_mainCam, COLOR_RGB2BGR);

    //OpenCV uses a different origin for the image, so it is flipped here.
    flip(m_mainCam, m_mainCam, 0);

    if (m_previewEnabled) {
        imshow(m_windowName, m_mainCam);
    }
}


void GeoDetection::setContours(const Mat &img, const Color::ColorName &color) {
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);


    // Watched a tutorial on YT about OpenCV. Lent a lot of openCV code from there in general https://www.youtube.com/watch?v=2FYm3GOonhk&t Chapter 6 and 7
    std::vector<std::vector<Point>> conPoly{contours.size()};
    for (int i{}; i < contours.size(); i++) {
        const double peri = arcLength(contours[i], true);
        approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

        //counts the number of corners in the detected object.
        const int objCor = static_cast<int>(conPoly[i].size());
        drawContours(m_mainCam, conPoly, i, Scalar(255, 0, 255), 2);

        //Chooses the shape of the object based on the number of corners.
        Rect tempBoundingRect = boundingRect(conPoly[i]);

        //Filters out small objects.
        if (tempBoundingRect.width < 10) {
            continue;
        }

        if (objCor == 4) {
            DetectedObjects currentObject(tempBoundingRect, ShapeColorHandler::Shapes::CUBE, color);
            m_detectedObjects.emplace_back(currentObject);
        } else {
            DetectedObjects currentObject(tempBoundingRect, ShapeColorHandler::Shapes::CIRCLE, color);
            m_detectedObjects.emplace_back(currentObject);
        }
    }
}

// OpenCV code from https://www.youtube.com/watch?v=2FYm3GOonhk&t Chapter 6 and 7

void GeoDetection::contourDetection() {
    //Applies HSV color space to the image.
    Mat mainCamHSV{};
    cvtColor(m_mainCam, mainCamHSV, COLOR_BGR2HSV);

    //Applies specific color mask to the image and detects shapes using setContours().
    Mat Mask{};
    const auto colorProfiles = m_colorProfiles.getSupportedColors();
    for (auto &i: colorProfiles) {

        inRange(mainCamHSV, m_colorProfiles.getColorProfile(i).first, m_colorProfiles.getColorProfile(i).second, Mask);
        setContours(Mask, i);
    }
}


GeoDetection::GeoDetection(std::string windowName, const std::pair<int, int> imageSize) : m_windowName(
                                                                                                  std::move(windowName)),
                                                                                          m_imageSize(imageSize),
                                                                                          m_pixels(imageSize.first * imageSize.second * 3) {}


std::vector<DetectedObjects<cv::Rect>> &GeoDetection::getDetectedObjects() {
    return m_detectedObjects;
}


void GeoDetection::cleanUp() {
    m_detectedObjects.clear();
}


void GeoDetection::previewDetection() {
    if (m_previewEnabled) {
        contourDetection();
        imshow(m_windowName, m_mainCam);
        cleanUp();
    }
}


void GeoDetection::enablePreview() {
    m_previewEnabled = true;
}


void GeoDetection::loadImg(const std::string &path) {
    m_mainCam = cv::imread(path, IMREAD_COLOR);
}


void GeoDetection::specialFunction() {
    cv::Mat test;
    test = cv::imread("data/testing_resources/images/test.jpg", cv::IMREAD_COLOR);
    cv::imshow("Test", test);
}
