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


KeyHandler::KeyHandler() = default;


void KeyHandler::update(
        GeoGen &generator,
        GeoDetection &detector,
        GeoManipulator &manipulator) const {

    if (m_spaceBarPressed) {
        manipulator.reArrangeMeshes(detector.runDetection());
    }
    if (m_rPressed) {
        generator.generateRND();
    }
    if (m_xPressed) {
        detector.previewDetection();
    }
    if (m_bSpacePressed) {
        GeoDetection::specialFunction();
    }
    if (m_tabPressed) {
        detector.enablePreview();
    }
}