#ifndef ENUM_SHAPE_HPP
#define ENUM_SHAPE_HPP
#include <map>
#include <opencv2/core/types.hpp>
#include <threepp/math/Color.hpp>


namespace shapeColorNS {
    /**
     * @brief Class for handling the supported colors and shapes.
     *   Supported colors are:
     *                      - green
     *                      - aqua
     *                      - orange
     *                      - red
     *
     *   Supported shapes are:
     *                      - CUBE
     *                      - CIRCLE
     */
    class ShapeColorHandler {
    private:
        const std::map<threepp::Color::ColorName, std::pair<cv::Scalar, cv::Scalar>> m_colorProfiles = {
                {threepp::Color::green, std::pair<cv::Scalar, cv::Scalar>(cv::Scalar(46, 0, 0), cv::Scalar(68, 255, 255))},
                {threepp::Color::aqua, std::pair<cv::Scalar, cv::Scalar>(cv::Scalar(76, 0, 0), cv::Scalar(90, 255, 255))},
                {threepp::Color::orange, std::pair<cv::Scalar, cv::Scalar>(cv::Scalar(13, 0, 0), cv::Scalar(32, 255, 255))},
                {threepp::Color::red, std::pair<cv::Scalar, cv::Scalar>(cv::Scalar(0, 32, 0), cv::Scalar(0, 255, 255))}};


    public:
        enum class Shapes {
            CUBE,
            CIRCLE,
            ENDOFENUM
        };


        ShapeColorHandler();


        [[nodiscard]] std::pair<cv::Scalar, cv::Scalar> getColorProfile(const threepp::Color::ColorName &color) const;


        [[nodiscard]] std::vector<threepp::Color::ColorName> getSupportedColors() const;


        [[nodiscard]] static std::vector<Shapes> getSupportedShapes();


        /**
         * @brief This function makes it possible to get a color based on an integer.
         *
         */
        [[nodiscard]] threepp::Color::ColorName getColorIntBased(int index) const;
    };
}// namespace shapeColorNS
#endif//ENUM_SHAPE_HPP
