#pragma once

#include "animation-base.hpp"
#include "const.h"
#include "single-color-breathing-animation.hpp"
#include "../logger.hpp"

class RainbowColorBreathingAnimation : public AnimationBase {
    public:
        RainbowColorBreathingAnimation(uint8_t minBrightness, int fullCycleDuration): singleColorBreathingAnimation(CHSV(random8(), 255, 255), minBrightness, fullCycleDuration) {}
        void tick();
        void begin(
            SetLedFunc setLeftStickLed, 
            GetLedFunc getLeftStickLed, 
            FadeToBlackFunc fadeLeftStickToBlack,
            SetLedFunc setRightStickLed,
            GetLedFunc getRightStickLed,
            FadeToBlackFunc fadeRightStickToBlack
        ) override;

    private:
        SingleColorBreathingAnimation singleColorBreathingAnimation;

};