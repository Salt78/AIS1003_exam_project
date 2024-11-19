#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include <map>
#include <vector>


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
        std::map<int, std::pair<float, float>> m_gridMap{};
        // A vector to store the used coordinates.
        std::vector<int> m_usedCoords{};


        void logUsedCoords(int key);

        void createGrid();

    public:
        explicit GridManager(std::pair<int, int> imageSize, float gridSize,
                             int spacing);

        [[nodiscard]] std::pair<float, float> getCoords(int key);

        [[nodiscard]] int getCoordQuantity() const;

        bool isUsed(int key);

        void resetUsedCoords() {
            m_usedCoords.clear();
        }
    };
}// namespace gridManagerNS


#endif//GRIDMANAGER_HPP
