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
        const std::pair<int, int> m_imageSize{};
        // The size of the grid. Always n X n
        const float m_gridSize{};
        // The spacing between each assigned coordinate.
        const int m_spacing{};
        // A map to store the grid coordinates.
        std::map<int, std::pair<float, float> > m_gridMap{};
        // A vector to store the used coordinates.
        std::vector<int> m_usedCoords{};

        //TESTING
        std::string m_windowName{};
        Canvas m_canvas{};
        GLRenderer m_renderer{};
        std::shared_ptr<Scene> m_scene{};
        std::shared_ptr<OrthographicCamera> m_camera{};

        void logUsedCoords(int key);

    public:
        explicit GridManager(const std::string &windowName, std::pair<int, int> imageSize, float gridSize,
                             int spacing);;

        void createGrid();

        [[nodiscard]] std::pair<float, float> getCoords(int key);

        [[nodiscard]] int getCoordQuantity() const;

        bool isUsed(int key);

        auto &getScene() {
            return m_scene;
        }

        void startAnimation(const std::function<void()> &additionalCode);

    };
}


#endif //GRIDMANAGER_HPP
