#pragma once

#include "animation-base.hpp"
#include "const.h"

typedef std::function<void()> CycleCallback;

class SingleColorBreathingAnimation : public AnimationBase {
    public:
        SingleColorBreathingAnimation(CHSV color, uint8_t minBrightness, int fullCycleDuration) {
            this->color = color;
            this->reverse = false;
            this->minBrightness = minBrightness;
            this->brightness = minBrightness;
            uint8_t distanceToMaxBrightness = 255 - minBrightness;
            this->frameDuration = fullCycleDuration / (distanceToMaxBrightness * 2);
        }
        void tick();
        void setColor(CHSV color);
        void setCycleCallback(CycleCallback callback);

    private:
        CHSV color;
        int frameDuration;
        bool reverse;
        uint8_t brightness;
        uint8_t minBrightness;
        CycleCallback cycleCallback;
        int skippedFrames = 0;
};