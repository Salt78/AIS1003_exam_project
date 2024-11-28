#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP
#include <map>
#include <vector>

namespace gridManagerNS {

    class GridManager {
    private:
        const std::pair<int, int> m_imageSize;
        const int m_spacing;
        const std::pair<int, int> m_startingCoords;
        std::map<int, std::pair<float, float>> m_gridMap{};
        std::vector<int> m_usedCoords{};

        void checkForExceptions() const;

        void logUsedCoords(int key);

        void createGrid();

        [[nodiscard]] int calcGridSize() const;

    public:
        explicit GridManager(std::pair<int, int> imageSize, int spacing = 50, std::pair<int, int> startingCoords = {25, 25});

        [[nodiscard]] std::pair<float, float> getCoords(int key);

        [[nodiscard]] int getCoordQuantity() const;

        bool isUsed(int key);

        void resetUsedCoords();
    };
}// namespace gridManagerNS


#endif//GRIDMANAGER_HPP
