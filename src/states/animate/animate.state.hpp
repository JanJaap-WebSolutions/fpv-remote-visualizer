#pragma once

#include <bluefairy.h>

#include "../basic.state.hpp"
#include "../../animations/rainbow-color-breathing-animation.hpp"
#include "../../animations/stick-reactive-animation.hpp"
#include "const.h"

enum AnimationType {
    ANIMATION_TYPE_OFF,
    ANIMATION_TYPE_ARMED,
    ANIMATION_TYPE_ARMED_HIGH_THROTTLE,
    ANIMATION_TYPE_DISARMED
};

class AnimateState: public BasicState {
    public:
        AnimateState(
            AppStateMachine *stateMachine,
            bluefairy::Scheduler *scheduler,
            LedController *ledController
        ): BasicState(
            stateMachine,
            scheduler,
            ledController
        ),
        _armedAnimation(),
        _disarmedAnimation(0, 255)
        {};

        void enter();
        void leave();
    
    private:
        StickReactiveAnimation _armedAnimation;
        RainbowColorBreathingAnimation _disarmedAnimation;
        bluefairy::TaskNode *_updateTask;
        bluefairy::TaskNode *_lampTask;
        AnimationType _activeAnimation;

        void updateAnimation();
        void enableArmedAnimation();
};
