#include "keyHandler.hpp"
#include <iostream>

using namespace threepp;
using namespace geoGenNS;
using namespace geoDetectionNS;
using namespace geoManipulatorNS;


void KeyHandler::onKeyPressed(const KeyEvent evt) {

    switch (evt.key) {
        case Key::SPACE:
            m_spaceBarPressed = true;
            break;
        case Key::R:
            m_rPressed = true;
            break;
        case Key::X:
            m_xPressed = true;
            break;
        case Key::ENTER:
            m_bSpacePressed = true;
            break;
        case Key::TAB:
            m_tabPressed = true;
            break;
        default:
            break;
    }
}


void KeyHandler::onKeyReleased(const KeyEvent evt) {
    switch (evt.key) {
        case Key::SPACE:
            m_spaceBarPressed = false;
            break;
        case Key::R:
            m_rPressed = false;
            break;
        case Key::X:
            m_xPressed = false;
            break;
        case Key::ENTER:
            m_bSpacePressed = false;
            break;
        case Key::TAB:
            m_tabPressed = false;
            break;
        default:
            break;
    }
}


KeyHandler::KeyHandler(GeoGen &generator, GeoDetection &geoDetection, GeoManipulator &geoManipulator)
    : m_generator(generator), m_geoDetection(geoDetection), m_geoManipulator(geoManipulator) {}


void KeyHandler::update() const {
    if (m_spaceBarPressed) {
        m_geoDetection.runDetection();
        m_geoManipulator.reArrangeMeshes(m_geoDetection.getDetectedObjects());
    }
    if (m_rPressed) {
        m_geoDetection.cleanUp();
        m_generator.generateRND();
        m_geoManipulator.resetRunCounter();
    }
    if (m_xPressed) {
        m_geoDetection.previewDetection();
    }
    if (m_bSpacePressed) {
        GeoDetection::specialFunction();
    }
    if (m_tabPressed) {
        m_geoDetection.enablePreview();
    }
}