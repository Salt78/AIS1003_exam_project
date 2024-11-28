#ifndef DETECTEDOBJECTS_HPP
#define DETECTEDOBJECTS_HPP

#include "shapeColorHandler.hpp"
#include <opencv2/core.hpp>
#include <threepp/math/Color.hpp>

    using namespace cv;
    using namespace threepp;
    using namespace shapeColorHandlerNS;


    template<typename T>
    class DetectedObjects {
    private:
        T m_object{};
        ShapeColorHandler::Shapes m_shape{};
        Color m_color{};

    public:
        DetectedObjects(T &object, const ShapeColorHandler::Shapes &shape, const Color &color)
            : m_object{object}, m_shape{shape},
              m_color{color} {
        }
        DetectedObjects() = default;

        [[nodiscard]] T getObject() const {
            return m_object;
        }

        [[nodiscard]] ShapeColorHandler::Shapes getShape() const {
            return m_shape;
        }

        [[nodiscard]] Color getColor() const {
            return m_color;
        }
    };
#endif//DETECTEDOBJECTS_HPP
