#ifndef SCENERY_HPP
#define SCENERY_HPP

#include "gridManager.hpp"
#include "shapeColorHandler.hpp"
#include "threepp/threepp.hpp"


namespace geoGenNS {

    /**
     * @brief Class for generating random shapes and colors for a threepp::Scene with a GridManager.
     */
    class GeoGen {

    private:
        threepp::Scene &m_scene;
        gridManagerNS::GridManager &m_grid;
      int m_quantity{};
        float m_meshSize{};

        std::vector<std::shared_ptr<threepp::Mesh>> m_geoVec{};

        shapeColorNS::ShapeColorHandler shapeColorHandler{};


        template<typename T>
        void createMesh(std::shared_ptr<T> &geometry, std::shared_ptr<threepp::MeshBasicMaterial> &material);


        static shapeColorNS::ShapeColorHandler::Shapes randomShape();


        [[nodiscard]] threepp::Color::ColorName randomColor() const;


        void addToScene() const;


        void processMesh(shapeColorNS::ShapeColorHandler::Shapes shape, std::shared_ptr<threepp::MeshBasicMaterial> &material);


    public:
        GeoGen(threepp::Scene &scene, gridManagerNS::GridManager &grid, int quantity = 20, float meshSize = 40);


        /**
         * @brief Generates random shapes with random colors and adds them to the scene.
         * @param quantity number of shapes to generate.
         */
        void generateRND();
    };
}// namespace geoGenNS

#include "createMesh.tpp"


#endif//SCENERY_HPP
