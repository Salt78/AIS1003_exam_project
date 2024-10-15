#include "geoGeneration.hpp"

enum class Shape {
    CUBE,
    SPHERE,
    CYLINDER,
    CONE
};


class GeoGen {
private:
    std::string m_name{};
    std::string m_color{};
    int m_quantity{};
    Shape m_shape{};

public:
    GeoGen(std::string name, std::string color = "yellow", int quantity = 0, Shape shape)
        : m_name{std::move(name)}, m_color{std::move(color)}, m_quantity{quantity}, m_shape{shape} {
    }

    [[nodiscard]] std::string getName() const {
        return m_name;
    }

    [[nodiscard]] std::string getColor() const {
        return m_color;
    }

    [[nodiscard]] int getQuantity() const {
        return m_quantity;
    }

    [[nodiscard]] std::string getShape() const {
        switch(m_shape) {
            case Shape::CUBE:
                return "cube";
            case Shape::CONE:
                return "cone";
            case Shape::SPHERE:
                return "sphere";
            case Shape::CYLINDER:
                return "cylinder";
        }
    }


};
