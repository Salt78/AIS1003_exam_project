#ifndef GEOMANIPULATOR_HPP
#define GEOMANIPULATOR_HPP
#include <vector>
#include "DetectedObjects.hpp"
#include "threepp/threepp.hpp"

namespace geoManipulatorNS {
    using namespace geoDetectionNS;
    using namespace threepp;

    class GeoManipulator {
    private:
        void createBox3(const DetectedObjects &object) {
            Point objectTlCoords(object.getObject().tl());
            Point objectBrCoords(object.getObject().br());

            Box3 box(Vector3(objectTlCoords.x, objectTlCoords.y, -50),
                     Vector3(objectBrCoords.x, objectBrCoords.y, 50));
        }

    public:
        GeoManipulator() = default;

        void setup(const std::vector<DetectedObjects> &objects) {
        }
    };
}


#endif //GEOMANIPULATOR_HPP
