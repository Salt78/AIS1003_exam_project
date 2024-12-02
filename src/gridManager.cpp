#include "gridManager.hpp"

#include <algorithm>
#include <cassert>
#include <stdexcept>

using namespace gridManagerNS;


/**
 * @brief Important that the result of the calculation is an integer.
 * @return the size of the grid
 */
int GridManager::calcGridSize() const {
    const float gridSize = static_cast<float>(m_imageSize.first - 2 * m_startingCoords.first) / static_cast<float>(m_spacing);

    return static_cast<int>(gridSize);
}


void GridManager::resetUsedCoords() {
    m_usedCoords.clear();
}
//Googled to figure out what I could use in the standard library to sort a vector. https://www.digitalocean.com/community/tutorials/sorting-a-vector-in-c-plus-plus
// I originally landed on std::sort, but Clion recommended std::ranges::sort instead. The code is definitely cleaner.
void gridManagerNS::GridManager::logUsedCoords(const int key) {
    m_usedCoords.push_back(key);
    std::ranges::sort(m_usedCoords);
}


void GridManager::createGrid() {
    //Did know the pseudo code in detail, but got start help from GPT.
   const int gridSize = calcGridSize();
    int key{1};
    for (int i{}; i <= gridSize; i++) {
        for (int z{}; z <= gridSize; z++) {
            m_gridMap[key] = std::make_pair(
                    static_cast<float>(m_startingCoords.first) + static_cast<float>(z) * static_cast<float>(m_spacing),
                    static_cast<float>(m_startingCoords.second) + static_cast<float>(i) * static_cast<float>(m_spacing));

            key++;
        }
    }
}


GridManager::GridManager(
        const std::pair<int, int> imageSize,
        const int spacing,
        const std::pair<int, int> startingCoords)
    : m_imageSize(imageSize),
      m_spacing(spacing),
      m_startingCoords(startingCoords) {

    createGrid();
}


// Got some help to fix const correctness from GPT (using .at())
std::pair<float, float> GridManager::getCoords(const int key) {
    assert(key > 0);
    assert(key <= getCoordQuantity());

    logUsedCoords(key);
    return m_gridMap.at(key);
}


//I originally was recommended to use std::find https://stackoverflow.com/questions/571394/how-to-find-out-if-an-item-is-present-in-a-stdvector
//But the second most popular answer recommended std::binary_search instead, and it returns a boolean value so it is clean.
bool GridManager::isUsed(const int key) const {
    return std::ranges::binary_search(m_usedCoords.begin(), m_usedCoords.end(), key);
}


int GridManager::getCoordQuantity() const {
    return static_cast<int>(m_gridMap.size());
}


std::pair<int, int> GridManager::getImgSize() const {
    return m_imageSize;
}
