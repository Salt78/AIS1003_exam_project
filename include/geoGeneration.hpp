//
// Created by Andreas on 13.10.2024.
//

#ifndef SCENERY_HPP
#define SCENERY_HPP

#include "threepp/threepp.hpp"
#include <numbers>
#include <random>


using namespace threepp;

// void addToScene(std::shared_ptr<Scene> &scene,std::vector<std::shared_ptr<Mesh> > &geoVec) {
//
//
//
// }

namespace geoGen {
    enum class Shape {
        CUBE,
        CIRCLE,
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

    //ThreePP properties
    std::shared_ptr<MeshBasicMaterial> m_material;
    std::vector<std::shared_ptr<Mesh> > m_geoVec{};

public:
    GeoGen(int quantity = 0, geoGen::Shape shape = geoGen::Shape::CUBE,
           Color::ColorName color = Color::red);


    [[nodiscard]] Color::ColorName getColor() const;

    [[nodiscard]] int getQuantity() const;

    [[nodiscard]] std::string getShape() const;

    [[nodiscard]] std::vector<std::shared_ptr<Mesh> > getGeoVec() const;

    void generate();

    void addToScene(const std::shared_ptr<Scene> &scene);
};




#endif //SCENERY_HPP
