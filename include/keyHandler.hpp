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
    bool m_spaceBarPressed{false};
    bool m_rPressed{false};
    bool m_xPressed{false};
    bool m_bSpacePressed{false};
    bool m_tabPressed{false};

    void onKeyPressed(threepp::KeyEvent evt) override;


    void onKeyReleased(threepp::KeyEvent evt) override;


public:
    KeyHandler();


    /**
     * @brief Updates the scene according to the key events.
     */
    void update(
            geoGenNS::GeoGen &generator,
            geoDetectionNS::GeoDetection &detector,
            geoManipulatorNS::GeoManipulator &manipulator) const;
};
#endif//KEYLISTENER_HPP
