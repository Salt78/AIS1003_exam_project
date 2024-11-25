#ifndef KEYLISTENER_HPP
#define KEYLISTENER_HPP

#include "geoDetection.hpp"
#include <threepp/threepp.hpp>

using namespace threepp;
using namespace geoDetectionNS;


class KeyHandler : public KeyListener {
private:
    GeoDetection &m_geoDetection;
    GeoManipulator &m_geoManipulator;

    bool m_spaceBarPressed{false};
    bool m_rPressed{false};


public:
    explicit KeyHandler(GeoDetection &geoDetection, GeoManipulator &geoManipulator) : m_geoDetection(geoDetection), m_geoManipulator(geoManipulator) {}

    void onKeyPressed(KeyEvent evt) override {
        if (evt.key == Key::SPACE) {
            m_spaceBarPressed = true;
        }
        if (evt.key == Key::R) {
            m_rPressed = true;
        }
    }

    void onKeyReleased(KeyEvent evt) override {
        if (evt.key == Key::SPACE) {
            m_spaceBarPressed = false;
        }
        if (evt.key == Key::R) {
            m_rPressed = false;
        }
    }

    void update() {
        if (m_spaceBarPressed) {
            m_geoDetection.contourDetection();
            m_geoManipulator.reArrangeMeshes(m_geoDetection.getDetectedObjects());
        }
        /*if (m_rPressed) {
            m_geoDetection.getDetectedObjects().clear();
        }*/
    }
};
#endif//KEYLISTENER_HPP
