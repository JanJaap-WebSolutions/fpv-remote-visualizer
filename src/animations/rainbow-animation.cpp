#include "rainbow-animation.hpp"

void RainbowAnimation::tick() {
    EVERY_N_MILLISECONDS(15) {
        for (int i = 0; i < LEFT_STICK_NUM_LEDS; i++) {
            int ledHue = this->hue + (i * 20);
            if (ledHue > 255) {
                ledHue -= 255;
            }
            int leftIndex = i;
            if (LEFT_STICK_LED_IS_INVERTED) {
                leftIndex = LEFT_STICK_NUM_LEDS - leftIndex;
            }
            this->setLeftStickLed(leftIndex, CHSV(ledHue, 255, 255));
        }

        for (int i = 0; i < RIGHT_STICK_NUM_LEDS; i++) {
            int ledHue = this->hue + (i * 20);
            if (ledHue > 255) {
                ledHue -= 255;
            }
            int rightIndex = i;
            if (RIGHT_STICK_LED_IS_INVERTED) {
                rightIndex = RIGHT_STICK_NUM_LEDS - rightIndex;
            }
            this->setRightStickLed(rightIndex, CHSV(ledHue, 255, 255));
        }

        this->hue++;
    }
}