#include "gridManager.hpp"
#include <algorithm>

//Googled to figure out what I could use in the standard library to sort a vector. https://www.digitalocean.com/community/tutorials/sorting-a-vector-in-c-plus-plus
// I originally landed on std::sort, but Clion recommended std::ranges::sort instead. The code is definitely cleaner.
void gridManagerNS::GridManager::logUsedCoords(int key) {
    m_usedCoords.push_back(key);
    std::ranges::sort(m_usedCoords);
}

void gridManagerNS::GridManager::createGrid() {
    const float centerImage = static_cast<float>(m_imageSize.first) / 2;
    const float centerGrid = m_gridSize / 2;

    const std::pair<float, float> startingCoords{
            centerImage - centerGrid * static_cast<float>(m_spacing),
            centerImage - centerGrid * static_cast<float>(m_spacing)};
    //Did know the pseudo code in detail, but got some small help from GPT
    int key{1};
    for (int i{}; static_cast<float>(i) < m_gridSize; i++) {
        for (int z{}; static_cast<float>(z) < m_gridSize; z++) {
            m_gridMap[key] = std::make_pair(
                    startingCoords.first + static_cast<float>(z) * static_cast<float>(m_spacing),
                    startingCoords.second + static_cast<float>(i) * static_cast<float>(m_spacing));

            key++;
        }
    }
}

gridManagerNS::GridManager::GridManager(
        const std::pair<int, int> imageSize,
        const float gridSize,
        const int spacing)
    : m_imageSize(imageSize),
      m_gridSize(gridSize),
      m_spacing(spacing) { createGrid(); }


// Got some help to fix const correctness from GPT (using .at())
std::pair<float, float> gridManagerNS::GridManager::getCoords(const int key) {
    logUsedCoords(key);
    return m_gridMap.at(key);
}

//I originally was recommended to use std::find https://stackoverflow.com/questions/571394/how-to-find-out-if-an-item-is-present-in-a-stdvector
//But the second most popular answer recommended std::binary_search instead, and it returns a boolean value so it is clean.
bool gridManagerNS::GridManager::isUsed(const int key) {
    return std::ranges::binary_search(m_usedCoords.begin(), m_usedCoords.end(), key);
}

int gridManagerNS::GridManager::getCoordQuantity() const {
    return static_cast<int>(m_gridMap.size());
}
