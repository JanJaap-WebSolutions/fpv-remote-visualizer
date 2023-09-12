#include "stick-reactive-animation.hpp"

void StickReactiveAnimation::tick() {
    mapSticks();
    render();
}

void StickReactiveAnimation::mapLeftStick() {
    int leftStickPosUpDown = this->trimStickPos(RX::throttle);
    int leftStickPosLeftRight = this->trimStickPos(RX::yaw);

    this->leftStickTargetDegree = this->stickPosToDegree(leftStickPosUpDown, leftStickPosLeftRight);
}

void StickReactiveAnimation::mapRightStick() {
    int rightStickPosUpDown = this->trimStickPos(RX::pitch);
    int rightStickPosLeftRight = this->trimStickPos(RX::roll);

    this->rightStickTargetDegree = this->stickPosToDegree(rightStickPosUpDown, rightStickPosLeftRight);
}

void StickReactiveAnimation::mapSticks() {
    this->mapLeftStick();
    this->mapRightStick();
}


void StickReactiveAnimation::render() {
    for (int i = 0; i < LEFT_STICK_NUM_LEDS; i++) {
        this->setLeftStickLed(i, CRGB::Red);
    }
    for (int i = 0; i < RIGHT_STICK_NUM_LEDS; i++) {
        this->setRightStickLed(i, CRGB::Blue);
    }

    int leftStickLedIndex = this->degreeToIndex(this->leftStickTargetDegree, LEFT_STICK_NUM_LEDS, LEFT_STICK_LED_START_OFFSET);
    if (LEFT_STICK_LED_IS_INVERTED) {
        leftStickLedIndex = LEFT_STICK_NUM_LEDS - leftStickLedIndex;
    }
    this->setLeftStickLed(leftStickLedIndex, CRGB::Green);

    int rightStickLedIndex = this->degreeToIndex(this->rightStickTargetDegree, RIGHT_STICK_NUM_LEDS, RIGHT_STICK_LED_START_OFFSET);
    if (RIGHT_STICK_LED_IS_INVERTED) {
        rightStickLedIndex = RIGHT_STICK_NUM_LEDS - rightStickLedIndex;
    }
    this->setRightStickLed(rightStickLedIndex, CRGB::White);
}

int StickReactiveAnimation::trimStickPos(int originalVal) {
    if (originalVal < 1000) {
        return 1000;
    } else if (originalVal > 2000) {
        return 2000;
    } else {
        return originalVal;
    }
}

/**
 * @brief Convert a degree to an led index, the leds are arranged in a circle
 * 
 * @param degree The degree to convert
 * @param maxIndex The maximum index of the led
 * @return int The index of the led (0-maxIndex)
*/
int StickReactiveAnimation::degreeToIndex(int degree, int maxIndex, int offset) {
    int index = (int) (degree / 360.0 * maxIndex);
    index += offset;

    while (index < 0) {
        index += maxIndex;
    }

    while (index >= maxIndex) {
        index -= maxIndex;
    }

    return index;
}

/**
 * @brief Convert a stick position to a degree, the stick points to a direction on a circle
 * 
 * @param stickPosUpDown The up/down position of the stick (1000-2000, 1500 is middle)
 * @param stickPosLeftRight The left/right position of the stick (1000-2000, 1500 is middle)
 * @return int The degree of the stick
*/
int StickReactiveAnimation::stickPosToDegree(int stickPosUpDown, int stickPosLeftRight) {
    int x2 = stickPosLeftRight - 1500;
    int y2 = stickPosUpDown - 1500;

    int deltaX = x2 - 0;
    int deltaY = y2 - 0;

    float radiant = atan2(deltaY, deltaX);

    float deg = radiant * 180.0 / PI;

    return deg + 180;
}