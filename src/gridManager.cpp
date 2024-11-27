#include "gridManager.hpp"
#include <algorithm>

//Googled to figure out what I could use in the standard library to sort a vector. https://www.digitalocean.com/community/tutorials/sorting-a-vector-in-c-plus-plus
// I originally landed on std::sort, but Clion recommended std::ranges::sort instead. The code is definitely cleaner.
void gridManagerNS::GridManager::logUsedCoords(int key) {
    m_usedCoords.push_back(key);
    std::ranges::sort(m_usedCoords);
}

void gridManagerNS::GridManager::createGrid() {


    //Did know the pseudo code in detail, but got some small help from GPT
    int key{1};
    for (int i{}; i <= calcGrid(); i++) {
        for (int z{}; z <= calcGrid(); z++) {
            m_gridMap[key] = std::make_pair(
                    static_cast<float>(m_startingCoords.first) + static_cast<float>(z) * static_cast<float>(m_spacing),
                    static_cast<float>(m_startingCoords.second) + static_cast<float>(i) * static_cast<float>(m_spacing));

            key++;
        }
    }
}

gridManagerNS::GridManager::GridManager(
        const std::pair<int, int> imageSize,
        const int spacing,
        const std::pair<int, int> startingCoords)
    : m_imageSize(imageSize),
      m_spacing(spacing),
      m_startingCoords(startingCoords) { createGrid(); }


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
