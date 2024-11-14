#ifndef DETECTEDOBJECTS_HPP
#define DETECTEDOBJECTS_HPP

#include <opencv2/core.hpp>
#include <threepp/math/Color.hpp>

namespace geoDetectionNS {
    using namespace cv;
    using namespace threepp;

    enum class Shape {
        CUBE,
        CIRCLE,
    };

    template<typename T>
    class DetectedObjects {
    private:
        T m_object{};
        Shape m_shape{};
        Color m_color{};

    public:
        DetectedObjects(T &object, const Shape &shape, const Color &color)
            : m_object{object}, m_shape{shape},
              m_color{color} {
        }

        [[nodiscard]] Rect getObject() const {
            return m_object;
        }

        [[nodiscard]] Shape getShape() const {
            return m_shape;
        }

        [[nodiscard]] Color getColor() const {
            return m_color;
        }
    };
}
#endif //DETECTEDOBJECTS_HPP
