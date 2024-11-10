#ifndef DETECTEDOBJECTS_HPP
#define DETECTEDOBJECTS_HPP

#include <opencv2/core.hpp>
#include <threepp/math/Color.hpp>

namespace geoDetectionNS {
    using namespace cv;

    enum class Shape {
        CUBE,
        CIRCLE,
    };

    class DetectedObjects {
    private:
        Rect m_object{};
        Shape m_shape{};
        threepp::Color m_color{};

    public:
        DetectedObjects(Rect &object, Shape shape, threepp::Color color)
            : m_object{object}, m_shape{shape},
              m_color{color} {
        }

        [[nodiscard]] Rect getObject() const {
            return m_object;
        }

        [[nodiscard]] Shape getShape() const {
            return m_shape;
        }

        [[nodiscard]] threepp::Color getColor() const {
            return m_color;
        }

        void setObject(const Rect &object) {
            m_object = object;
        }

        void setShape(const Shape &shape) {
            m_shape = shape;
        }

        void setColor(const threepp::Color &color) {
            m_color = color;
        }
    };
}
#endif //DETECTEDOBJECTS_HPP
