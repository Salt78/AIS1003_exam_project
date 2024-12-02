#ifndef CREATEMESH_TPP
#define CREATEMESH_TPP

using namespace threepp;

namespace geoGenNS {
    template<typename T>
    void GeoGen::createMesh(std::shared_ptr<T> &geometry, std::shared_ptr<MeshBasicMaterial> &material) {
        int randomKey{math::randInt(1, m_grid.getCoordQuantity())};
        while (m_grid.isUsed(randomKey)) {
            randomKey = math::randInt(1, m_grid.getCoordQuantity());
        }

        m_geoVec.push_back(Mesh::create(geometry, material));
        m_geoVec.back()->position.set(m_grid.getCoords(randomKey).first, m_grid.getCoords(randomKey).second, 0);
    }
}// namespace geoGenNS
#endif//CREATEMESH_TPP
