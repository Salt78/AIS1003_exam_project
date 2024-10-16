//
// Created by Andreas on 13.10.2024.
//

#ifndef SCENERY_HPP

#include "threepp/threepp.hpp"
#include <iostream>


using namespace threepp;

namespace geoGen {
    enum class Shape {
        CUBE,
        SPHERE,
        CYLINDER,
        CONE
    };
}


class GeoGen {
private:
    //General properties
    Color::ColorName m_color{};
    int m_quantity{};
    geoGen::Shape m_shape{};

    std::shared_ptr<MeshBasicMaterial> m_material;

    std::vector<std::shared_ptr<Mesh> > m_geoVec{};

public:
    GeoGen(int quantity = 0, geoGen::Shape shape = geoGen::Shape::CUBE);


    [[nodiscard]] Color::ColorName getColor() const;

    [[nodiscard]] int getQuantity() const;

    [[nodiscard]] std::string getShape() const;

    std::vector<std::shared_ptr<Mesh> > getGeoVec() const;

    void generate();
};


#define SCENERY_HPP

#endif //SCENERY_HPP
