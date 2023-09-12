#include "single-color-breathing-animation.hpp"

void SingleColorBreathingAnimation::tick() {
    EVERY_N_MILLISECONDS(this->frameDuration) {
        if (this->reverse) {
            this->brightness--;
            if (this->brightness <= this->minBrightness) {
                this->reverse = false;
            }
        } else {
            this->brightness++;

            if (this->brightness == 255) {
                this->reverse = true;
            }
        }

        for (int i = 0; i < LEFT_STICK_NUM_LEDS; i++) {
            this->color.v = this->brightness;
            this->setLeftStickLed(i, this->color);
        }

        for (int i = 0; i < RIGHT_STICK_NUM_LEDS; i++) {
            this->color.v = this->brightness;
            this->setRightStickLed(i, this->color);
        }
    }
}