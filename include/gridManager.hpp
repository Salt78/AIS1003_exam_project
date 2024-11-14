#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include <map>
#include <vector>
#include <string>
#include <threepp/threepp.hpp>

using namespace threepp;

namespace gridManagerNS {
    class GridManager {
    private:
        // The size of the image. Should always be a square.
        std::pair<int, int> m_imageSize{};
        // The size of the grid. Always n X n
        float m_gridSize{};
        // The spacing between each assigned coordinate.
        int m_spacing{};
        // A map to store the grid coordinates.
        std::map<int, std::pair<float, float> > m_gridMap{};
        // A vector to store the used coordinates.
        std::vector<int> m_usedCoords{};

        //TESTING
        std::string m_windowName{};
        Canvas m_canvas;
        GLRenderer m_renderer{};
        std::shared_ptr<Scene> m_scene{};
        std::shared_ptr<OrthographicCamera> m_camera{};


        //Googled to figure out what I could use in the standard library to sort a vector. https://www.digitalocean.com/community/tutorials/sorting-a-vector-in-c-plus-plus
        // I originally landed on std::sort, but Clion recommended std::ranges::sort instead. The code is definitely cleaner.
        void logUsedCoords(int key);

    public:
        explicit GridManager(const std::string &windowName, std::pair<int, int> imageSize, float gridSize,
                             int spacing);;


        void createGrid();

        // Got some help to fix const correctness from GPT (using .at())
        std::pair<float, float> getCoords(int key);

        //I originally was recommended to use std::find https://stackoverflow.com/questions/571394/how-to-find-out-if-an-item-is-present-in-a-stdvector
        //But the second most popular answer recommended std::binary_search instead when dealing with larger vectors.
        bool isUsed(int key);

        [[nodiscard]] int getCoordQuantity() const;

        auto &getScene() {
            return m_scene;
        }

        //Did get help from GPT to figure out how I could make a method accept a lambda.
        void startAnimation(const std::function<void()> &additionalCode) {
            Clock clock;
            m_canvas.animate([&]() {
                m_renderer.render(*m_scene, *m_camera);
                additionalCode();
            });
        }
        auto &getCanvas() {
            return m_canvas;
        }
        auto getCamera() {
            return m_camera;
        }
        auto &getRenderer() {
            return m_renderer;
        }
    };
}


#endif //GRIDMANAGER_HPP
