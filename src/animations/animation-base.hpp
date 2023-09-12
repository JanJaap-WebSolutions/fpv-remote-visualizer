#pragma once

#include <FastLED.h>
#include <functional>

/**
 * Sets the led at a certain index to a certain color
 * @param index index of led
*/
typedef std::function<void(int, CRGB)> SetLedFunc;

/**
 * Gets the led at a certain index
 * @param index index of led
*/
typedef std::function<CRGB(int)> GetLedFunc;

/**
 * Fades all leds by a certain amount to black
 * @param fadeAmount amount to fade by
*/
typedef std::function<void(int)> FadeToBlackFunc;

class AnimationBase {
    public:
        AnimationBase() {
            // set dummy as default
            this->setLeftStickLed = [](int index, CRGB color) {};
            this->getLeftStickLed = [](int index) { return CRGB::Black; };
            this->fadeLeftStickToBlack = [](int index) {};
            this->setRightStickLed = [](int index, CRGB color) {};
            this->getRightStickLed = [](int index) { return CRGB::Black; };
            this->fadeRightStickToBlack = [](int index) {};
        };
        void begin(
            SetLedFunc setLeftStickLed, 
            GetLedFunc getLeftStickLed, 
            FadeToBlackFunc fadeLeftStickToBlack,
            SetLedFunc setRightStickLed,
            GetLedFunc getRightStickLed,
            FadeToBlackFunc fadeRightStickToBlack
        ) {
            this->setLeftStickLed = setLeftStickLed;
            this->getLeftStickLed = getLeftStickLed;
            this->fadeLeftStickToBlack = fadeLeftStickToBlack;
            this->setRightStickLed = setRightStickLed;
            this->getRightStickLed = getRightStickLed;
            this->fadeRightStickToBlack = fadeRightStickToBlack;
        };
        virtual void tick() = 0;
    
    protected:
        SetLedFunc setLeftStickLed;
        GetLedFunc getLeftStickLed;
        FadeToBlackFunc fadeLeftStickToBlack;
        SetLedFunc setRightStickLed;
        GetLedFunc getRightStickLed;
        FadeToBlackFunc fadeRightStickToBlack;
};