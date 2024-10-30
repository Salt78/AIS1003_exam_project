//
// Created by Andreas on 30.10.2024.
//

#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include <map>
#include <utility>

class GridManager {
private:
    float m_gridSize{};
    float m_imageSize{};
    int m_spacing{};
    std::map<int, std::pair<float, float> > m_gridMap{};

public:
    GridManager(float imageSize, float gridSize = 14, int spacing = 50)
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
                int xCoord = startingCoords.first + z * m_spacing;
                int yCoord = startingCoords.second + i * m_spacing;
                key++;
            }
        }
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
