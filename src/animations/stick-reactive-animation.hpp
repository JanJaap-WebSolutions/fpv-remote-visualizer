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
        void mapSticks();
        void mapLeftStick();
        void mapRightStick();
        void render();
        int trimStickPos(int originalVal);
        int degreeToIndex(int degree, int maxIndex, int offset);
        int stickPosToDegree(int stickPosUpDown, int stickPosLeftRight);
        int leftStickTargetDegree;
        int rightStickTargetDegree;
};