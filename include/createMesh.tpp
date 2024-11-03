#ifndef CREATEMESH_TPP
#define CREATEMESH_TPP

template<typename T>
void GeoGen::createMesh(GridManager &grid, std::shared_ptr<T> &geometry) {
    // Random number generator https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, grid.getCoordQuantity());

    for (int i{}; i < m_quantity; i++) {
        int randomKey{dist(rd)};

        while (grid.isUsed(randomKey)) {
            randomKey = dist(rd);
        }

        m_geoVec.push_back(Mesh::create(geometry, m_material));
        m_geoVec[i]->position.set(grid.getCoords(randomKey).first, grid.getCoords(randomKey).second, 0);

        //Got some help from copilot for comparing the type of the geometry
        if (typeid(T) == typeid(CircleGeometry)) {
            m_geoVec[i]->rotation.x = std::numbers::pi;
        }
    }
}


#endif //CREATEMESH_TPP
