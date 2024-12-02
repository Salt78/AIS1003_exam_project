#ifndef SCENERY_HPP
#define SCENERY_HPP

#include "gridManager.hpp"
#include "threepp/threepp.hpp"


namespace geoGenNS {

    /**
     * @brief Generates random shapes and colors for a threepp::Scene with a GridManager.
     */
    class GeoGen {

    private:
        threepp::Scene &m_scene;
        gridManagerNS::GridManager &m_grid;
        int m_quantity;
        float m_meshSize{40};

        //Stores the generated geometries.
        std::vector<std::shared_ptr<threepp::Mesh>> m_geoVec{};

        enum class Shape {
            CUBE,
            CIRCLE
        };


        template<typename T>
        void createMesh(std::shared_ptr<T> &geometry, std::shared_ptr<threepp::MeshBasicMaterial> &material);

        static Shape randomShape() ;

        [[nodiscard]] static threepp::Color::ColorName randomColor();

        void addToScene() const;

        void processMesh(Shape shape, std::shared_ptr<threepp::MeshBasicMaterial> &material);

        void cleanUp();


    public:
        GeoGen(threepp::Scene &scene, gridManagerNS::GridManager &grid, int quantity = 40);


        /**
         * @brief Generates random shapes with random colors and adds them to the scene.
         *
         */
        void generateRND();
    };
}// namespace geoGenNS

#include "createMesh.tpp"


#endif//SCENERY_HPP
