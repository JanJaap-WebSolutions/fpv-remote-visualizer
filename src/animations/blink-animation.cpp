#include "blink-animation.hpp"

void BlinkAnimation::tick() {
    EVERY_N_MILLISECONDS(this->intervalMs) {
        CRGB color = this->on ? this->onColor : this->offColor;
        
        for (int i = 0; i < LEFT_STICK_NUM_LEDS; i++) {
            this->setLeftStickLed(i, color);
        }
        for (int i = 0; i < RIGHT_STICK_NUM_LEDS; i++) {
            this->setRightStickLed(i, color);
        }

        this->on = !this->on;
    }
}