#ifndef KEYLISTENER_HPP
#define KEYLISTENER_HPP

#include "geoDetection.hpp"
#include "geoGeneration.hpp"
#include "geoManipulator.hpp"
#include <threepp/threepp.hpp>

using namespace threepp;
using namespace geoDetectionNS;
using namespace geoGenNS;


class KeyHandler : public KeyListener {
private:
    GeoGen &m_generator;
    GeoDetection &m_geoDetection;
    GeoManipulator &m_geoManipulator;

    bool m_spaceBarPressed{false};
    bool m_rPressed{false};
    bool m_xPressed{false};


public:
    explicit KeyHandler(GeoGen &generator, GeoDetection &geoDetection, GeoManipulator &geoManipulator)
        : m_generator(generator), m_geoDetection(geoDetection), m_geoManipulator(geoManipulator) {}

    void onKeyPressed(KeyEvent evt) override {
        if (evt.key == Key::SPACE) {
            m_spaceBarPressed = true;
        }
        if (evt.key == Key::R) {
            m_rPressed = true;
        }
        if (evt.key == Key::X) {
            m_xPressed = true;
        }
    }

    void onKeyReleased(KeyEvent evt) override {
        if (evt.key == Key::SPACE) {
            m_spaceBarPressed = false;
        }
        if (evt.key == Key::R) {
            m_rPressed = false;
        }
        if (evt.key == Key::X) {
            m_xPressed = false;
        }
    }

    void update() {
        if (m_spaceBarPressed) {
            m_geoDetection.contourDetection();
            m_geoManipulator.reArrangeMeshes(m_geoDetection.getDetectedObjects());
        }
        if (m_rPressed) {
            m_geoDetection.cleanUp();
            m_geoManipulator.cleanUp();

            m_generator.generateRND();
        }
        if (m_xPressed) {
            m_geoDetection.previewDetection();
        }
    }
};
#endif//KEYLISTENER_HPP
