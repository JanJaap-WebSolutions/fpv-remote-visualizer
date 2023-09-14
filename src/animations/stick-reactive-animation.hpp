#pragma once

#include "animation-base.hpp"
#include "const.h"
#include "../rx.hpp"
#include "../logger.hpp"

#define StickReactiveAnimationRippleMaxSteps 16

class StickReactiveAnimation : public AnimationBase {
    public:
        void tick();

    private:
        bool mapSticks();
        void render();
        int trimStickPos(int originalVal);
        int degreeToIndex(int degree, int maxIndex, int offset, bool isInverted);
        int stickPosToDegree(int stickPosUpDown, int stickPosLeftRight);
        bool mapLeftStick();
        bool mapRightStick();
        void renderRightStick();
        void renderLeftStick();
        int getRightStickLedIntensity(int ledIndex);
        int rightStickTargetDegree;
        int leftStickHuePos = 0;
        int leftStickIntensity;
        void onStickChange();
};