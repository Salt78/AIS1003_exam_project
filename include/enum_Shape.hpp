#ifndef ENUM_SHAPE_HPP
#define ENUM_SHAPE_HPP
#include <map>
#include <opencv2/core.hpp>
#include <threepp/math/Color.hpp>

using namespace threepp;
using namespace cv,

        enum class Shapes {
            CUBE,
            CIRCLE,
            ENDOFENUM
        };

class ColorManager {

private:
    const std::map<Color::ColorName, std::pair<Scalar, Scalar>> m_colorProfiles = {
            {Color::green, std::pair<Scalar, Scalar>(Scalar(46, 0, 0), Scalar(68, 255, 255))},
            {Color::aqua, std::pair<Scalar, Scalar>(Scalar(76, 0, 0), Scalar(90, 255, 255))},
            {Color::orange, std::pair<Scalar, Scalar>(Scalar(13, 0, 0), Scalar(32, 255, 255))},
            {Color::red, std::pair<Scalar, Scalar>(Scalar(0, 32, 0), Scalar(0, 255, 255))}};

public:
    ColorManager();

    [[nodiscard]] std::pair<Scalar, Scalar> getColorProfile(const Color::ColorName &color) const {
        return m_colorProfiles.at(color);
    };
};

#endif//ENUM_SHAPE_HPP
