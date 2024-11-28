#include "gridManager.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace gridManagerNS;

void GridManager::checkForExceptions() const {
    //When i first started writing this exception i did get help from GTP, because I didn't know how to throw exceptions.
    if (m_imageSize.first != m_imageSize.second) {
        throw std::invalid_argument("Only nXn images are supported");
    }
    if (m_imageSize.first <= 0 || m_imageSize.second <= 0) {
        throw std::invalid_argument("Image size must be positive");
    }
    if (m_spacing <= 0) {
        throw std::invalid_argument("Spacing must be positive");
    }
    if (m_startingCoords.first < 0 || m_startingCoords.second < 0) {
        throw std::invalid_argument("Starting coordinates must be positive");
    }
}


int GridManager::calcGridSize() const {
    const float gridSize = static_cast<float>(m_imageSize.first - 2 * m_startingCoords.first) / static_cast<float>(m_spacing);

    //GPT helped me with this part. I was unsure how to check if the value is float or int.
    if (gridSize != std::floor(gridSize)) {
        throw std::invalid_argument("gridCalculation results in non-integer");
    }
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
    int key{1};
    for (int i{}; i <= calcGridSize(); i++) {
        for (int z{}; z <= calcGridSize(); z++) {
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

    checkForExceptions();
    createGrid();
}


// Got some help to fix const correctness from GPT (using .at())
std::pair<float, float> GridManager::getCoords(const int key) {
    if (key == 0 || key > getCoordQuantity()) {
        throw std::invalid_argument("Key is out of bounds");
    }

    logUsedCoords(key);
    return m_gridMap.at(key);
}


//I originally was recommended to use std::find https://stackoverflow.com/questions/571394/how-to-find-out-if-an-item-is-present-in-a-stdvector
//But the second most popular answer recommended std::binary_search instead, and it returns a boolean value so it is clean.
bool GridManager::isUsed(const int key) {
    return std::ranges::binary_search(m_usedCoords.begin(), m_usedCoords.end(), key);
}


int GridManager::getCoordQuantity() const {
    return static_cast<int>(m_gridMap.size());
}
