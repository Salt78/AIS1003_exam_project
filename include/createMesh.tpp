#ifndef CREATEMESH_TPP
#define CREATEMESH_TPP

#include <random>



namespace geoGenNS {
    template<typename T>
    void GeoGen::createMesh(std::shared_ptr<T> &geometry, std::shared_ptr<threepp::MeshBasicMaterial> &material) {
        // Random number generator https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(1, m_grid.getCoordQuantity());

        int randomKey{dist(rd)};
        while (m_grid.isUsed(randomKey)) {
            randomKey = dist(rd);
        }

        m_geoVec.push_back(threepp::Mesh::create(geometry, material));
        m_geoVec.back()->position.set(m_grid.getCoords(randomKey).first, m_grid.getCoords(randomKey).second, 0);
    }
}// namespace geoGenNS
#endif//CREATEMESH_TPP
