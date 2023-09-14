#include "rainbow-color-breathing-animation.hpp"
#include "../logger.hpp"

void RainbowColorBreathingAnimation::tick() {
    this->singleColorBreathingAnimation.tick();
}

void RainbowColorBreathingAnimation::begin(
    SetLedFunc setLeftStickLed, 
    GetLedFunc getLeftStickLed, 
    FadeToBlackFunc fadeLeftStickToBlack,
    SetLedFunc setRightStickLed,
    GetLedFunc getRightStickLed,
    FadeToBlackFunc fadeRightStickToBlack
) {
    Logger::getInstance().logLn("RainbowColorBreathingAnimation - begin");
    this->singleColorBreathingAnimation.begin(
        setLeftStickLed,
        getLeftStickLed,
        fadeLeftStickToBlack,
        setRightStickLed,
        getRightStickLed,
        fadeRightStickToBlack
    );

    this->singleColorBreathingAnimation.setCycleCallback([this]() {
        this->singleColorBreathingAnimation.setColor(CHSV(random8(), 255, 255));
    });
}