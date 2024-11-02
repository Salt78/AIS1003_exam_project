//
// Created by Andreas on 30.10.2024.
//

#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include <map>
#include <vector>
#include <algorithm>

class GridManager {
private:
    // The size of the image. Should always be a square.
    float m_imageSize{};
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
    void logUsedCoords(int key) {
        m_usedCoords.push_back(key);
        std::ranges::sort(m_usedCoords);
    }

public:
    explicit GridManager(float imageSize, float gridSize, int spacing)
        : m_imageSize(imageSize), m_gridSize(gridSize), m_spacing(spacing) {
    };


    void createGrid() {
        const float centerImage = m_imageSize / 2;
        const float centerGrid = m_gridSize / 2;

        const std::pair<float, float> startingCoords{
            centerImage - centerGrid * m_spacing, centerImage - centerGrid * m_spacing
        };

        int key{1};
        for (int i{}; i < m_gridSize; i++) {
            for (int z{}; z < m_gridSize; z++) {
                m_gridMap[key] = std::make_pair(startingCoords.first + z * m_spacing,
                                                startingCoords.second + i * m_spacing);
                // DEBUG
                //int xCoord = startingCoords.first + z * m_spacing;
                //int yCoord = startingCoords.second + i * m_spacing;
                key++;
            }
        }
    }

    // Got some help to fix const correctness from GPT (using .at())
    std::pair<int, int> getCoords(const int key) {
        logUsedCoords(key);
        return m_gridMap.at(key);
    }

    //I originally was recommended to use std::find https://stackoverflow.com/questions/571394/how-to-find-out-if-an-item-is-present-in-a-stdvector
    //But the second most popular answer recommended std::binary_search instead when dealing with larger vectors.
    bool isUsed(int key) {
        return std::binary_search(m_usedCoords.begin(), m_usedCoords.end(), key);
    }

    // auto getTestValue(int key) const {
    //     auto test = m_gridMap.find(key);
    //
    //     auto returnValue = test->second;
    //
    //     return returnValue;
    // }
};


#endif //GRIDMANAGER_HPP
