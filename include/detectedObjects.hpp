#ifndef DETECTEDOBJECTS_HPP
#define DETECTEDOBJECTS_HPP

#include "enum_Shape.hpp"
#include <opencv2/core.hpp>
#include <threepp/math/Color.hpp>

namespace geoDetectionNS {
    using namespace cv;
    using namespace threepp;


    template<typename T>
    class DetectedObjects {
    private:
        T m_object{};
        Shapes m_shape{};
        Color m_color{};

    public:
        DetectedObjects(T &object, const Shapes &shape, const Color &color)
            : m_object{object}, m_shape{shape},
              m_color{color} {
        }

        [[nodiscard]] T getObject() const {
            return m_object;
        }

        [[nodiscard]] Shapes getShape() const {
            return m_shape;
        }

        [[nodiscard]] Color getColor() const {
            return m_color;
        }
    };
}// namespace geoDetectionNS
#endif//DETECTEDOBJECTS_HPP
