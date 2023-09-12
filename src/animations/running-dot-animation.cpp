#include "running-dot-animation.hpp"

void RunningDotAnimation::tick() {
    EVERY_N_MILLISECONDS(this->stepDuration) {
        for(int i = 0; i < LEFT_STICK_NUM_LEDS; i++) {
            this->setLeftStickLed(i, this->backgroundColor);
        }

        if (!this->reverse) {
            this->currentLeftStickLedIndex++;
            if (this->currentLeftStickLedIndex >= LEFT_STICK_NUM_LEDS) {
                this->currentLeftStickLedIndex = LEFT_STICK_NUM_LEDS -2;
                this->reverse = true;
                cycles++;
            }
        } else {
            this->currentLeftStickLedIndex--;
            if (this->currentLeftStickLedIndex < 0) {
                this->currentLeftStickLedIndex = 1;
                this->reverse = false;
                cycles++;
            }
        }

        if (this->cycles >= this->maxCycles && this->maxCycles != -1) {
            if (!this->completed) {
                this->completed = true;
                this->completedCallback();
            }
            return;
        }

        int leftIndexToSet = this->currentLeftStickLedIndex;
        if (LEFT_STICK_LED_IS_INVERTED) {
            leftIndexToSet = LEFT_STICK_NUM_LEDS - leftIndexToSet;
        }
        this->setLeftStickLed(leftIndexToSet, this->dotColor);
    }

    EVERY_N_MILLISECONDS(this->stepDuration) {
        for(int i = 0; i < RIGHT_STICK_NUM_LEDS; i++) {
            this->setRightStickLed(i, this->backgroundColor);
        }

        if (!this->reverse) {
            this->currentRightStickLedIndex++;
            if (this->currentRightStickLedIndex >= RIGHT_STICK_NUM_LEDS) {
                this->currentRightStickLedIndex = RIGHT_STICK_NUM_LEDS -2;
                this->reverse = true;
                cycles++;
            }
        } else {
            this->currentRightStickLedIndex--;
            if (this->currentRightStickLedIndex < 0) {
                this->currentRightStickLedIndex = 1;
                this->reverse = false;
                cycles++;
            }
        }

        if (this->cycles >= this->maxCycles && this->maxCycles != -1) {
            if (!this->completed) {
                this->completed = true;
                this->completedCallback();
            }
            return;
        }

        int rightIndexToSet = this->currentRightStickLedIndex;
        if (RIGHT_STICK_LED_IS_INVERTED) {
            rightIndexToSet = RIGHT_STICK_NUM_LEDS - rightIndexToSet;
        }
        this->setRightStickLed(rightIndexToSet, this->dotColor);
    }
}

void RunningDotAnimation::onCompleted(CompletedCallback callback) {
    this->completedCallback = callback;
}