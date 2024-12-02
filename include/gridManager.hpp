#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include <unordered_map>
#include <vector>

namespace gridManagerNS {

    /**
     * Class that creates and manages coordinates for mesh objects.
     * The class creates x amounts of usable coords, based on the image size and spacing.
     * It's important to note that the starting coords, spacing and image size must be coordinated together with the size of the meshes.
     *
     */
    class GridManager {
    private:
        const std::pair<int, int> m_imageSize;
        const int m_spacing;
        const std::pair<int, int> m_startingCoords;
        std::unordered_map<int, std::pair<float, float>> m_gridMap;
        std::vector<int> m_usedCoords;


        void logUsedCoords(int key);

        void createGrid();

        [[nodiscard]] int calcGridSize() const;

    public:
        /**
         * @param imageSize The size of the image.
         * @param spacing The amount of space between each coordinate.
         * @param startingCoords Where the first coordinate should be placed.
         */
        explicit GridManager(std::pair<int, int> imageSize, int spacing = 50, std::pair<int, int> startingCoords = {25, 25});

        /**
         * @brief Get the coordinates for a given key.
         * The first key is for the smallest set of coordinates and the last key is for the largest set of coordinates.
         * NB: It also logs the key as used internally.
         *
         * @param key Each coordinate has a key, which is used to get the coordinates.
         * @return Coordinates for given key.
         */
        [[nodiscard]] std::pair<float, float> getCoords(int key);

        [[nodiscard]] int getCoordQuantity() const;

        [[nodiscard]] bool isUsed(int key) const;

        void resetUsedCoords();

        [[nodiscard]] std::pair<int, int> getImgSize() const;
    };
}// namespace gridManagerNS


#endif//GRIDMANAGER_HPP
