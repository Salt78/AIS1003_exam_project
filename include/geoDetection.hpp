#ifndef GEODETECTION_HPP
#define GEODETECTION_HPP

#include "detectedObjects.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>
#include <threepp/threepp.hpp>
#include <vector>


namespace geoDetectionNS {

    /**
     * @brief The GeoDetection class is responsible for detecting shapes and colors in a given image.
                    The image can be extracted from a threepp::GLRenderer object or loaded from a file (testing purposes).
     */
    class GeoDetection {
    private:
        //Constructor properties
        const std::string m_windowName{};
        const std::pair<int, int> m_imageSize{};

        //For detection logic
        std::vector<unsigned char> m_pixels{};
        cv::Mat m_mainCam{};
        std::vector<DetectedObjects<cv::Rect>> m_detectedObjects{};

        //Misc
        shapeColorHandlerNS::ShapeColorHandler m_colorProfiles{};


        void setContours(cv::Mat &img, const threepp::Color::ColorName &color);


    public:
        GeoDetection(std::string windowName, std::pair<int, int> imageSize);


        /**
         * @brief Reads the pixels from a threepp::GLRenderer object and stores them.
         * @param renderer The renderer object from which the image will be extracted.
         */
        void setupVirtualCam(threepp::GLRenderer &renderer);


        /**
         * @brief Detects contours and colors of shapes in the image.
         *             The detected objects are stored and can be accessed with getDetectedObjects().
         */
        void contourDetection();


        [[nodiscard]] std::vector<DetectedObjects<cv::Rect>> getDetectedObjects() const;


        /**
         * @brief Used to show a preview of the detection process in a OpenCV window.
         *             The method showPreview() must be called in the animation loop to display the window.
         */
        void previewDetection();


        /**
         * @brief Shows a preview of the detection process.
         */
        void showPreview() const;


        /**
         * @brief Readies the object for a new detection process.
         */
        void cleanUp();


        /**
         * @brief Makes it possible to load images manually for testing purposes.
         * @param path The path to the image file.
         */
        void loadImg(const std::string &path);
    };
}// namespace geoDetectionNS
#endif//GEODETECTION_HPP
