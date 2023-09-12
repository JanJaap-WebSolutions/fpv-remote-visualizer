
#include <Arduino.h>
#include <bluefairy.h>

#include "const.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "logger.hpp"
#include "app-state.hpp"
#include "led-controller.hpp"
#include "states/booting/booting.state.hpp"
#include "states/ota/ota.state.hpp"
#include "states/animate/animate.state.hpp"
#include "states/lamp/lamp.state.hpp"
#include "rx.hpp"

bluefairy::Scheduler logicScheduler;
bluefairy::Scheduler headTrackerScheduler;
bluefairy::Scheduler ledScheduler;
AppStateMachine stateMachine;
LedController ledController;

OTAState otaState(&stateMachine, &logicScheduler, &ledController);
BootingState bootingState(&stateMachine, &logicScheduler, &ledController);
AnimateState animateState(&stateMachine, &logicScheduler, &ledController);
LampState lampState(&stateMachine, &logicScheduler, &ledController);

inline void ledTaskHandlerSetup() {
  Logger::getInstance().logLn("ledTaskHandlerSetup() - starting");
  int frameDuration = 1000 / LED_FPS;

  ledController.begin();

  Logger::getInstance().logLn("ledTaskHandlerSetup() - scheduling ledController.tick() every " + String(frameDuration) + "ms");
  ledScheduler.every(
      frameDuration,
      []() {
          ledController.tick();
          ledController.setBrightness(RX::ledBrightness);
      }
  );

  Logger::getInstance().logLn("ledTaskHandlerSetup() - done");
}

inline void ledTaskHandlerLoop() {
  ledScheduler.loop();
}

inline void setupStateMachine() {
  Logger::getInstance().logLn("logicTaskHandlerSetup() - preparing state machine");
  stateMachine[AppState::APP_STATE_BOOTING] = bootingState;
  stateMachine[AppState::APP_STATE_OTA] = otaState;
  stateMachine[AppState::APP_STATE_ANIMATE] = animateState;
  stateMachine[AppState::APP_STATE_LAMP] = lampState;

  Logger::getInstance().logLn("logicTaskHandlerSetup() - starting state machine");
  stateMachine.toState(AppState::APP_STATE_BOOTING);

  Logger::getInstance().logLn("logicTaskHandlerSetup() - done");
}

void setup()
{
  Logger::getInstance().begin();
  Logger::getInstance().logLn("Welcome to CRSF Visualizer");

  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

  setupStateMachine();
  RX::begin();
  logicScheduler.every(1, []() { RX::loop(); });

  xTaskCreateUniversal(
      [] (void *pvParameter) {
        ledTaskHandlerSetup();

        for (;;) {
          ledTaskHandlerLoop();
        }
      },
      "LED",
      10000,
      NULL,
      0,
      NULL,
      -1
  );

  xTaskCreateUniversal(
      [] (void *pvParameter) {
          for (;;) {
              logicScheduler.loop();
          }
      },
      "Logic",
      10000,
      NULL,
      1,
      NULL,
      -1
  );

  Logger::getInstance().logLn("setup() done, starting loop()");
}

void loop() {
}