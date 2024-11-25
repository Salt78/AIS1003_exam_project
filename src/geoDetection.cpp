#include "geoDetection.hpp"
void geoDetectionNS::GeoDetection::setupVirtualCam(GLRenderer &renderer) {
    //Pixels are read into the buffer here.

    renderer.readPixels({0, 0}, m_imageSize, Format::RGB, m_pixels.data());

    //Creates an OPENCV Mat object for the pixels. (https://stackoverflow.com/questions/38489423/c-convert-rgb-1-d-array-to-opencv-mat-image)
    Mat mainCam_RGB = Mat(m_imageSize.second, m_imageSize.first, CV_8UC3, m_pixels.data());
    cvtColor(mainCam_RGB, m_mainCam, COLOR_RGB2BGR);

    //OpenCV uses a different origin for the image, so it is flipped here.
    flip(m_mainCam, m_mainCam, 0);
}

void geoDetectionNS::GeoDetection::setContours(Mat &img, const Color::ColorName &color) {
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);


    // Wached a tutorial on YT about OpenCV. Lent a lot of code from there in general https://www.youtube.com/watch?v=2FYm3GOonhk&t
    std::vector<std::vector<Point>> conPoly{contours.size()};
    for (int i{}; i < contours.size(); i++) {
        double peri = arcLength(contours[i], true);
        approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

        const int objCor = static_cast<int>(conPoly[i].size());
        drawContours(m_mainCam, conPoly, i, Scalar(255, 0, 255), 2);

        Rect tempBoundingRect{boundingRect(conPoly[i])};
        if (objCor == 4) {
            DetectedObjects currentObject(tempBoundingRect, ShapeColorHandler::Shapes::CUBE, color);
            m_detectedObjects.emplace_back(currentObject);
        } else {
            DetectedObjects currentObject(tempBoundingRect, ShapeColorHandler::Shapes::CIRCLE, color);
            m_detectedObjects.emplace_back(currentObject);
        }
    }
}


void geoDetectionNS::GeoDetection::contourDetection() {
    //Applies HSV color space to the image.
    Mat mainCamHSV{};
    cvtColor(m_mainCam, mainCamHSV, COLOR_BGR2HSV);

    //Applies a mask to the image.
    Mat Mask{};
    auto colorProfiles = m_colorProfiles.getSupportedColors();
    for (auto &i: colorProfiles) {
        inRange(mainCamHSV, m_colorProfiles.getColorProfile(i).first, m_colorProfiles.getColorProfile(i).second, Mask);
        setContours(Mask, i);
    }
}


geoDetectionNS::GeoDetection::GeoDetection(std::string windowName, std::pair<int, int> imageSize) : m_windowName(
                                                                                                            std::move(windowName)),
                                                                                                    m_imageSize(imageSize),
                                                                                                    m_pixels(imageSize.first * imageSize.second * 3) {
    namedWindow(m_windowName, WINDOW_AUTOSIZE);
}


void geoDetectionNS::GeoDetection::imageProcessing(const bool showCam) {

    if (showCam == true) {
        imshow(m_windowName, m_mainCam);
    }
}

