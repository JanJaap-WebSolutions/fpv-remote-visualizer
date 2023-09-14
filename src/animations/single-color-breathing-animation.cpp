#include "single-color-breathing-animation.hpp"
#include "../logger.hpp"

void SingleColorBreathingAnimation::tick() {
    EVERY_N_MILLISECONDS(this->frameDuration) {
        if (this->brightness == 0) {
            while (this->skippedFrames < 10) {
                this->skippedFrames++;
                return;
            }
            this->skippedFrames = 0;
        }
        if (this->reverse) {
            this->brightness--;
            if (this->brightness <= this->minBrightness) {
                this->reverse = false;
                if (this->cycleCallback) {
                    this->cycleCallback();
                }
            }
        } else {
            this->brightness++;

            if (this->brightness == 255) {
                this->reverse = true;
            }
        }

        this->color.value = this->brightness;
        for (int i = 0; i < LEFT_STICK_NUM_LEDS; i++) {
            this->setLeftStickLed(i, this->color);
        }

        for (int i = 0; i < RIGHT_STICK_NUM_LEDS; i++) {
            this->setRightStickLed(i, this->color);
        }
    }
}

void SingleColorBreathingAnimation::setColor(CHSV color) {
    this->color = color;
}

void SingleColorBreathingAnimation::setCycleCallback(CycleCallback callback) {
    this->cycleCallback = callback;
}