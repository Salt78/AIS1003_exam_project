#include "keyHandler.hpp"

using namespace threepp;
using namespace geoGenNS;
using namespace geoDetectionNS;
using namespace geoManipulatorNS;


void KeyHandler::onKeyPressed(const KeyEvent evt) {
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


void KeyHandler::onKeyReleased(const KeyEvent evt) {
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


KeyHandler::KeyHandler(GeoGen &generator, GeoDetection &geoDetection, GeoManipulator &geoManipulator)
    : m_generator(generator), m_geoDetection(geoDetection), m_geoManipulator(geoManipulator) {}


void KeyHandler::update() const {
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