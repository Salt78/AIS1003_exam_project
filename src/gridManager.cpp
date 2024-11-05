#include "gridManager.hpp"


void gridManagerNS::GridManager::logUsedCoords(int key) {
    m_usedCoords.push_back(key);
    std::ranges::sort(m_usedCoords);
}

gridManagerNS::GridManager::GridManager(int imageSize, float gridSize, int spacing): m_imageSize(imageSize),
    m_gridSize(gridSize), m_spacing(spacing) {
}

void gridManagerNS::GridManager::createGrid() {
    const float centerImage = static_cast<float>(m_imageSize) / 2;
    const float centerGrid = m_gridSize / 2;

    const std::pair<float, float> startingCoords{
        centerImage - centerGrid * static_cast<float>(m_spacing),
        centerImage - centerGrid * static_cast<float>(m_spacing)
    };

    int key{1};
    for (int i{}; static_cast<float>(i) < m_gridSize; i++) {
        for (int z{}; static_cast<float>(z) < m_gridSize; z++) {
            m_gridMap[key] = std::make_pair(
                startingCoords.first + static_cast<float>(z) * static_cast<float>(m_spacing),
                startingCoords.second + static_cast<float>(i) * static_cast<float>(m_spacing));
            // DEBUG
            //int xCoord = startingCoords.first + z * m_spacing;
            //int yCoord = startingCoords.second + i * m_spacing;
            key++;
        }
    }
}

std::pair<float, float> gridManagerNS::GridManager::getCoords(const int key) {
    logUsedCoords(key);
    return m_gridMap.at(key);
}

bool gridManagerNS::GridManager::isUsed(const int key) {
    return std::ranges::binary_search(m_usedCoords.begin(), m_usedCoords.end(), key);
}

int gridManagerNS::GridManager::getCoordQuantity() const {
    return static_cast<int>(m_gridMap.size());
}
