//
// Created by Andreas on 30.10.2024.
//

#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include <map>
#include <vector>
#include <algorithm>

namespace gridManager {
    class GridManager {
    private:
        // The size of the image. Should always be a square.
        int m_imageSize{};
        // The size of the grid. Always n X n
        float m_gridSize{};
        // The spacing between each assigned coordinate.
        int m_spacing{};
        // A map to store the grid coordinates.
        std::map<int, std::pair<float, float> > m_gridMap{};
        // A vector to store the used coordinates.
        std::vector<int> m_usedCoords{};


        //Googled to figure out what i could use in the standard library to sort a vector. https://www.digitalocean.com/community/tutorials/sorting-a-vector-in-c-plus-plus
        // I originally landed on std::sort, but Clion recommended std::ranges::sort instead. The code is definitely cleaner.
        void logUsedCoords(int key);

    public:
        explicit GridManager(int imageSize, float gridSize, int spacing);;


        void createGrid();

        // Got some help to fix const correctness from GPT (using .at())
        std::pair<float, float> getCoords(int key);

        //I originally was recommended to use std::find https://stackoverflow.com/questions/571394/how-to-find-out-if-an-item-is-present-in-a-stdvector
        //But the second most popular answer recommended std::binary_search instead when dealing with larger vectors.
        bool isUsed(const int key);

        [[nodiscard]] int getCoordQuantity() const;
    };
}


#endif //GRIDMANAGER_HPP
