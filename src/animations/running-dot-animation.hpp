#pragma once

#include "animation-base.hpp"
#include "const.h"
#include "../logger.hpp"

/**
 * Callback for when animation is completed
*/
typedef std::function<void()> CompletedCallback;

class RunningDotAnimation: public AnimationBase {
    public:
        RunningDotAnimation(uint32_t totalDurationMs, CRGB dotColor, CRGB backgroundColor, int maxCycles = -1): AnimationBase() {
            this->stepDuration = totalDurationMs / (LEFT_STICK_NUM_LEDS - 2);
            this->dotColor = dotColor;
            this->backgroundColor = backgroundColor;
            this->maxCycles = maxCycles;
        }
        void tick() override;
        void onCompleted(CompletedCallback callback);

    private:
        int currentLeftStickLedIndex = 4;
        int currentRightStickLedIndex = 4;
        uint32_t stepDuration;
        bool reverse = false;
        CRGB dotColor;
        CRGB backgroundColor;
        int maxCycles;
        int cycles = 0;
        CompletedCallback completedCallback;
        bool completed = false;
};