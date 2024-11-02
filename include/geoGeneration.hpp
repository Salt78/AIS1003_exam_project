//
// Created by Andreas on 13.10.2024.
//

#ifndef SCENERY_HPP
#define SCENERY_HPP

#include "threepp/threepp.hpp"
#include <numbers>
#include <random>
#include "gridManager.hpp"


using namespace threepp;
using namespace gridManager;

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
        CAPSULE
    };
}


class GeoGen {
private:
    //General properties
    float m_meshSize{};
    int m_quantity{};
    geoGen::Shape m_shape{};
    Color::ColorName m_color{};


    //ThreePP properties
    std::shared_ptr<MeshBasicMaterial> m_material;
    std::vector<std::shared_ptr<Mesh> > m_geoVec{};

    template<typename T>
    void createMesh(GridManager &grid, std::shared_ptr<T> &geometry);

    void addToScene(Scene &scene);

public:
    explicit GeoGen(float meshSize = 40, int quantity = 4, geoGen::Shape shape = geoGen::Shape::CUBE,
                    Color::ColorName color = Color::red);


    [[nodiscard]] Color::ColorName getColor() const;

    [[nodiscard]] int getQuantity() const;

    [[nodiscard]] std::string getShape() const;

    [[nodiscard]] std::vector<std::shared_ptr<Mesh> > getGeoVec() const;

    void generate(GridManager &grid, Scene &scene);
};

#include "createMesh.tpp"

#endif //SCENERY_HPP
