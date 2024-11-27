#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include <map>
#include <vector>


namespace gridManagerNS {

    class GridManager {
    private:
        // The size of the image. Should always be a square.
        const std::pair<int, int> m_imageSize{};
        // The spacing between each assigned coordinate.
        const int m_spacing{};
        // The starting coordinates for the grid.
        std::pair<int, int> m_startingCoords{};
        // A map to store the grid coordinates.
        std::map<int, std::pair<float, float>> m_gridMap{};
        // A vector to store the used coordinates.
        std::vector<int> m_usedCoords{};


        void logUsedCoords(int key);

        void createGrid();

        [[nodiscard]] int calcGrid() const {
            const int gridSize = (m_imageSize.first - 2 * m_startingCoords.first) / m_spacing;
            return gridSize;
        }

    public:
        explicit GridManager(std::pair<int, int> imageSize, int spacing = 50, std::pair<int, int> startingCoords = {25, 25});

        [[nodiscard]] std::pair<float, float> getCoords(int key);

        [[nodiscard]] int getCoordQuantity() const;

        bool isUsed(int key);

        void resetUsedCoords() {
            m_usedCoords.clear();
        }
    };
}// namespace gridManagerNS


#endif//GRIDMANAGER_HPP
