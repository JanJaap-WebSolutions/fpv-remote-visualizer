#include "solid-color-animation.hpp"

void SolidColorAnimation::tick() {
    EVERY_N_MILLISECONDS(500) {
        for (int i = 0; i < LEFT_STICK_NUM_LEDS; i++) {
            this->setLeftStickLed(i, color);
        }

        for (int i = 0; i < RIGHT_STICK_NUM_LEDS; i++) {
            this->setRightStickLed(i, color);
        }
    }
}