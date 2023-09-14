#include "stick-reactive-animation.hpp"
#include "../logger.hpp"

void StickReactiveAnimation::tick() {
    mapSticks();
    render();
}

bool StickReactiveAnimation::mapLeftStick() {
    int trimmedYaw = this->trimStickPos(RX::yaw);

    // only move hue if yaw is not in the middle
    int hueMoveSpeed = 0;

    if (trimmedYaw < 1450 || trimmedYaw > 1550) {
        hueMoveSpeed = map(trimmedYaw, 1000, 2000, -5, 5);
    }

    this->leftStickHuePos += hueMoveSpeed;

    int trimmedThrottle = this->trimStickPos(RX::throttle);
    int newIntensity = map(trimmedThrottle, 1000, 2000, 50, 255);

    this->leftStickIntensity = newIntensity;

    return hueMoveSpeed != 0 || newIntensity != this->leftStickIntensity;
}

bool StickReactiveAnimation::mapRightStick() {
    int upDownPos = this->trimStickPos(RX::pitch);
    int leftRightPos = this->trimStickPos(RX::roll);

   int newTargetDegree = this->stickPosToDegree(upDownPos, leftRightPos);

   this->rightStickTargetDegree = newTargetDegree;

    return newTargetDegree != this->rightStickTargetDegree;
}

bool StickReactiveAnimation::mapSticks() {
    bool leftChanged = this->mapLeftStick();
    bool rightChanged = this->mapRightStick();

    return leftChanged || rightChanged;
}

void StickReactiveAnimation::renderLeftStick() {
    for (int i = 0; i < LEFT_STICK_NUM_LEDS; i++) {
        int ledHue = this->leftStickHuePos + (i * (255 / LEFT_STICK_NUM_LEDS));
        if (ledHue > 255) {
            ledHue -= 255;
        }
        this->setLeftStickLed(i, CHSV(ledHue, 255, this->leftStickIntensity));
    }
}

void StickReactiveAnimation::renderRightStick() {
    for (int i = 0; i < RIGHT_STICK_NUM_LEDS; i++) {
        int ledHue = i * (255 / RIGHT_STICK_NUM_LEDS);
        if (ledHue > 255) {
            ledHue -= 255;
        }
        this->setRightStickLed(i, CHSV(ledHue, 255, this->getRightStickLedIntensity(i)));
    }
}

/**
 * @brief Get the intensity of a led on the right stick
 * it gets brighter the closer the led is to the target degree
 * and also the further the stick is pushed to the side, this is determined by the max value of either up/down or left/right
 * 
 * @param ledIndex The index of the led
 * @return int The intensity of the led
*/
int StickReactiveAnimation::getRightStickLedIntensity(int ledIndex) {
    int targetedLedIndex = this->degreeToIndex(
        this->rightStickTargetDegree, 
        RIGHT_STICK_NUM_LEDS, 
        RIGHT_STICK_LED_START_OFFSET,
        RIGHT_STICK_LED_IS_INVERTED
    );

    int distance = 0;
    int checkedIndex = ledIndex;
    while (checkedIndex != targetedLedIndex) {
        if (checkedIndex > RIGHT_STICK_NUM_LEDS - 1) {
            checkedIndex = 0;
        }
        
        distance++;
        checkedIndex++;
    }

    if (distance > RIGHT_STICK_NUM_LEDS / 2) {
        distance = RIGHT_STICK_NUM_LEDS - distance;
    }

    int trimmedUpDownPos = this->trimStickPos(RX::pitch);
    int trimmedLeftRightPos = this->trimStickPos(RX::roll);

    int upDownDistanceFromCenter = abs(trimmedUpDownPos - 1500);
    int leftRightDistanceFromCenter = abs(trimmedLeftRightPos - 1500);

    int maxStickPos = max(upDownDistanceFromCenter, leftRightDistanceFromCenter);

    if (maxStickPos < 0) {
        maxStickPos = 0;
    }

    if (maxStickPos > 500) {
        maxStickPos = 500;
    }

    int maxIlluminatedDistance = map(maxStickPos, 0, 500, 0, RIGHT_STICK_NUM_LEDS / 4);

    int trimmedDistance = distance;
    if (trimmedDistance > maxIlluminatedDistance) {
        trimmedDistance = maxIlluminatedDistance;
    }

    if (trimmedDistance < 0) {
        trimmedDistance = 0;
    }

    int intensity = 0;
    if (maxIlluminatedDistance > 0) {
        intensity = map(trimmedDistance, 0, maxIlluminatedDistance, 255, 0);
    }

    if (intensity < 0) {
        intensity = 0;
    }

    int maxBrightness = map(maxStickPos, 0, 500, 0, 255);

    return map(intensity, 0, 255, 30, maxBrightness);
}

void StickReactiveAnimation::render() {
    this->renderLeftStick();
    this->renderRightStick();
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
int StickReactiveAnimation::degreeToIndex(int degree, int maxIndex, int offset, bool isInverted) {
    int index = (int) (degree / 360.0 * maxIndex);
    index += offset;

    while (index < 0) {
        index += maxIndex;
    }

    while (index >= maxIndex) {
        index -= maxIndex;
    }

    if (isInverted) {
        index = maxIndex - index;
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

/*void StickReactiveAnimation::begin() {
    Logger::getInstance().logLn("StickReactiveAnimation::begin()");
    RX::setAnimationOnChannelChangedCallback([this]() {
        xTaskCreateUniversal(
            [] (void *pvParameter) {
                StickReactiveAnimation *animation = (StickReactiveAnimation *) pvParameter;
                animation->onStickChange();
            },
            "StickReactiveAnimation-onStickChange",
            1024,
            this,
            0,
            NULL,
            -1
        );
        this->onStickChange();
    });
    Logger::getInstance().logLn("StickReactiveAnimation::begin() - done");
}*/

/*void StickReactiveAnimation::end() {
    Logger::getInstance().logLn("StickReactiveAnimation::end()");
    RX::clearAnimationOnChannelChangedCallback();
    Logger::getInstance().logLn("StickReactiveAnimation::end() - done");
}*/