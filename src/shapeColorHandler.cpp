#include "shapeColorHandler.hpp"

using namespace threepp;
using namespace cv;
using namespace shapeColorHandlerNS;

ShapeColorHandler::ShapeColorHandler() = default;


std::pair<Scalar, Scalar> ShapeColorHandler::getColorProfile(const Color::ColorName &color) const {
    return m_colorProfiles.at(color);
}


std::vector<Color::ColorName> ShapeColorHandler::getSupportedColors() const {
    std::vector<Color::ColorName> supportedColors{};
    for (const auto &i: m_colorProfiles) {
        supportedColors.push_back(i.first);
    }
    return supportedColors;
}


//GPT showed me how I could use ENDOFENUM to get this done.
std::vector<ShapeColorHandler::Shapes> ShapeColorHandler::getSupportedShapes() {
    std::vector<Shapes> supportedShapes{};
    for (int i{}; i < static_cast<int>(Shapes::ENDOFENUM); i++) {
        supportedShapes.push_back(static_cast<Shapes>(i));
    }
    return supportedShapes;
}


Color::ColorName ShapeColorHandler::getColorIntBased(const int index) const {
    const std::vector<std::pair<Color::ColorName, std::pair<Scalar, Scalar>>> mapVector(m_colorProfiles.begin(), m_colorProfiles.end());
    return mapVector[index].first;
}