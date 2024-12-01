#ifndef DETECTEDOBJECTS_HPP
#define DETECTEDOBJECTS_HPP

#include "shapeColorHandler.hpp"
#include <threepp/math/Color.hpp>


/**
 * @brief Stores detected objects.
 * Makes the  job of assigning a color and a shape to an object easier.
 * @tparam T The type of the object.
 *                     - cv::Rect
 *                     - std::shared_ptr<threepp::Mesh>
 */
template<typename T>
class DetectedObjects {
private:
    T m_object{};
    shapeColorNS::ShapeColorHandler::Shapes m_shape{};
    threepp::Color m_color{};

public:
    DetectedObjects(const T &object, const shapeColorNS::ShapeColorHandler::Shapes &shape, const threepp::Color &color)
        : m_object{object}, m_shape{shape},
          m_color{color} {
    }
    DetectedObjects() = default;

    [[nodiscard]] T getObject() const {
        return m_object;
    }

    [[nodiscard]] shapeColorNS::ShapeColorHandler::Shapes getShape() const {
        return m_shape;
    }

    [[nodiscard]] threepp::Color getColor() const {
        return m_color;
    }
};
#endif//DETECTEDOBJECTS_HPP
