#ifndef KEYLISTENER_HPP
#define KEYLISTENER_HPP

#include "geoDetection.hpp"
#include "geoGeneration.hpp"
#include "geoManipulator.hpp"
#include <threepp/threepp.hpp>

/**
 * @brief Handles key events
 */
class KeyHandler final : public threepp::KeyListener {
private:
    geoGenNS::GeoGen &m_generator;
    geoDetectionNS::GeoDetection &m_geoDetection;
    geoManipulatorNS::GeoManipulator &m_geoManipulator;

    bool m_spaceBarPressed{false};
    bool m_rPressed{false};
    bool m_xPressed{false};
    bool m_bSpacePressed{false};
    bool m_tabPressed{false};

    void onKeyPressed(threepp::KeyEvent evt) override;


    void onKeyReleased(threepp::KeyEvent evt) override;


public:
    explicit KeyHandler(geoGenNS::GeoGen &generator, geoDetectionNS::GeoDetection &geoDetection, geoManipulatorNS::GeoManipulator &geoManipulator);


    /**
     * @brief Updates the scene according to the key events.
     */
    void update() const;
};
#endif//KEYLISTENER_HPP
