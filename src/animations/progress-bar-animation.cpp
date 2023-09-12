#include "progress-bar-animation.hpp"

void ProgressBarAnimation::tick() {
    EVERY_N_MILLISECONDS(100) {
        for(int i = 0; i < this->totalLeds; i++) {
            if (i <= this->maxLedIndexActive) {
                if (i < LEFT_STICK_NUM_LEDS) {
                    int leftIndex = i;
                    if (LEFT_STICK_LED_IS_INVERTED) {
                        leftIndex = LEFT_STICK_NUM_LEDS - leftIndex;
                    }
                    this->setLeftStickLed(leftIndex, this->barColor);
                    continue;
                }

                int rightIndex = i;
                if (RIGHT_STICK_LED_IS_INVERTED) {
                    rightIndex = RIGHT_STICK_NUM_LEDS - rightIndex;
                }
                this->setRightStickLed(rightIndex, this->barColor);
                continue;
            } else {
                if (i < LEFT_STICK_NUM_LEDS) {
                    int leftIndex = i;
                    if (LEFT_STICK_LED_IS_INVERTED) {
                        leftIndex = LEFT_STICK_NUM_LEDS - leftIndex;
                    }
                    this->setLeftStickLed(leftIndex, this->backgroundColor);
                    continue;
                }
                int rightIndex = i;
                if (RIGHT_STICK_LED_IS_INVERTED) {
                    rightIndex = RIGHT_STICK_NUM_LEDS - rightIndex;
                }
                this->setRightStickLed(rightIndex, this->backgroundColor);
            }
        }
    }
};

void ProgressBarAnimation::setProgress(uint8_t progress) {
    // map progress (0-100) to maxLedIndexActive (0-NUM_LEDS)
    int newIndex = map(progress, 0, 100, 0, this->totalLeds);
    if (newIndex == this->maxLedIndexActive) {
        return;
    }

    this->maxLedIndexActive = newIndex;
}