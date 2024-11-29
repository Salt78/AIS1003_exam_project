#include "keyHandler.hpp"
#include <iostream>

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
    if (evt.key == Key::ENTER) {
        m_bSpacePressed = true;
    }
    if (evt.key == Key::TAB) {
        m_tabPressed = true;
        ;
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
    if (evt.key == Key::ENTER) {
        m_bSpacePressed = false;
    }
    if (evt.key == Key::TAB) {
        m_tabPressed = false;
        ;
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