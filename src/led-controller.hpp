#pragma once

#include "const.h"
#include <FastLED.h>
#include "animations/solid-color-animation.hpp"
#include "animations/animation-base.hpp"


class LedController {
    public:
        void begin();
        void tick();
        void setAnimation(AnimationBase *animation, bool clear = true);
        void clear();
        void setBrightness(uint8_t brightness);

    private:
        AnimationBase* currentAnimation;
        CRGBArray<LEFT_STICK_NUM_LEDS> leftStickLeds;
        CRGBArray<RIGHT_STICK_NUM_LEDS> rightStickLeds;
        uint8_t brightness = 255;
        SolidColorAnimation _emptyAnimation = SolidColorAnimation(CRGB::Black);
};
