//  example.ino
//
//  Copyright 2013 Paradise Arcade Shop, ParadiseArcadeShop.com
//  All rights reserved.  Use is subject to license terms.
//
//  Code is provided for entertainment purposes and use with the Kaimana controller.
//  Code may be copied, modified, resused with this Copyright notice.
//  No commercial use without written permission from Paradise Arcade Shop.
//
//  Paradise Arcade Shop Kaimana LED Driver Board
//  Initial Release October 15, 2013
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//  Kaimana example based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//
#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "kaimana.hpp"
#include "kaimana_custom.h"
// local function declarations
void  pollSwitches(void);
void pollSwitchesForTourneyMode(void);
void pollSwitchesForSettingSelection(void);
void pollSwitchesForSetting(void);
void pollSwitchesForPinLEDSettingSelection(void);
void pollSwitchesForPinLEDSetting(void);
void showStartup(void);
// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;

auto pollFunction = pollSwitchesForTourneyMode;
auto invert = false;
int tourneyButtonHoldTime = 0;
int settingButtonHoldTime = 0;
int pinLEDSettingButtonHoldTime = 0;
struct SettingLedButton {
    int pin;

    SettingLedButton()
    {
      reset();
    }

    bool isSet(void)
    {
      return pin != -1;
    }

    void reset(void)
    {
      pin = -1;
    }

    bool isSetOnMoveSide(void)
    {
      switch (pin)
      {
        case PIN_RIGHT:
        case PIN_DOWN:
        case PIN_LEFT:
        case PIN_UP:
          return true;
      }
      return false;
    }
} settingLedButton;

struct SettingPinLEDButton {
    int pin;

    SettingPinLEDButton()
    {
        reset();
    }

    bool isSet(void)
    {
      return pin != -1;
    }

    void reset(void)
    {
        pin = -1;
    }
} settingPinLEDButton;

// the setup routine runs first and once each time power is applied to the Kaimana board
void setup()
{
    // Serial.begin(115200);
}
// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop()
{
  // infinite loop of read switches, update LEDs and idle animation when necessary
  while(true)
  {
    pollFunction();
    // delay a little to avoid flickering (yea, updates happens really, really fast!)
    delay( MAIN_LOOP_DELAY );
  }
}
// ==============================================================
//
//  local functions start here
//
// ==============================================================
// light up all leds at boot to demonstrate everything is functional
//
void showStartup(void)
{
  kaimana.setALL(BLACK);
  delay(BOOT_COLOR_DELAY);
  kaimana.setALL(WHITE);
  delay(BOOT_COMPLETE_DELAY);
  kaimana.setALL(BLACK);
}

void showStartupSettingMode()
{
  kaimana.setAllLEDs();
  kaimana.updateALL();
}

void showStartupPinLEDSettingMode()
{
    for(auto i = 0; i < 2; i++)
    {
        kaimana.setALL(WHITE);
        delay(BOOT_COLOR_DELAY);
        kaimana.setALL(BLACK);
        delay(BOOT_COLOR_DELAY);
    }
}

void showShutdownSettingMode()
{
  kaimana.setALL(BLACK);
}

void pollSwitches(void)
{
  const uint8_t pins[] = {
    PIN_RIGHT,
    PIN_DOWN,
    PIN_LEFT,
    PIN_UP,
    PIN_P1,
    PIN_P2,
    PIN_P3,
    PIN_P4,
    PIN_K1,
    PIN_K2,
    PIN_K3,
    PIN_K4,
  };
  for(const auto pin: pins)
  {
    if(!digitalRead(pin) ^ invert)
    {
      kaimana.setLED(pin);
    }
    else
    {
      kaimana.setLED(pin, BLACK);
    }
  }

  if(!digitalRead(PIN_START))
  {
    tourneyButtonHoldTime += MAIN_LOOP_DELAY;
    // Do animations a once when moves to Tourney mode.
    if(tourneyButtonHoldTime >= TOURNEY_MODE_ENABLE_TIME && tourneyButtonHoldTime <= TOURNEY_MODE_ENABLE_TIME + MAIN_LOOP_DELAY)
    {
      showStartup();
    }
  }
  else
  {
    if(tourneyButtonHoldTime >= TOURNEY_MODE_ENABLE_TIME)
    {
      pollFunction = pollSwitchesForTourneyMode;
      kaimana.setALL(BLACK);
    }
    tourneyButtonHoldTime = 0;
  }
  if(!digitalRead(PIN_SELECT))
  {
    settingButtonHoldTime += MAIN_LOOP_DELAY;
    if(settingButtonHoldTime >= SETTING_MODE_ENABLE_TIME)
    {
      showStartupSettingMode();
    }
  }
  else
  {
    if(settingButtonHoldTime >= SETTING_MODE_ENABLE_TIME)
    {
      showStartupSettingMode();
      pollFunction = pollSwitchesForSettingSelection;
    }
    settingButtonHoldTime = 0;
  }
  if(!digitalRead(PIN_HOME))
  {
    pinLEDSettingButtonHoldTime += MAIN_LOOP_DELAY;
    if(pinLEDSettingButtonHoldTime >= SETTING_MODE_ENABLE_TIME)
    {
        showStartupPinLEDSettingMode();
    }
  }
  else
  {
    if(pinLEDSettingButtonHoldTime >= SETTING_MODE_ENABLE_TIME)
    {
      showStartupPinLEDSettingMode();
      kaimana.resetAllLEDs();
      pollFunction = pollSwitchesForPinLEDSettingSelection;
    }
    pinLEDSettingButtonHoldTime = 0;
  }

  // update the leds with new/current colors in the array
  kaimana.updateALL();
}

void pollSwitchesForTourneyMode(void)
{
  if(!digitalRead(PIN_START))
  {
    tourneyButtonHoldTime += MAIN_LOOP_DELAY;
    // Do animations a once when moves to non-tourney mode.
    if(tourneyButtonHoldTime >= TOURNEY_MODE_ENABLE_TIME && tourneyButtonHoldTime <= TOURNEY_MODE_ENABLE_TIME + MAIN_LOOP_DELAY)
    {
      invert = !digitalRead(PIN_UP);
      showStartup();
    }
  }
  else
  {
    if(tourneyButtonHoldTime >= TOURNEY_MODE_ENABLE_TIME)
    {
      pollFunction = pollSwitches;
    }
    tourneyButtonHoldTime = 0;
  }
}

void pollSwitchesForSettingSelection(void)
{
  static auto show = showStartupSettingMode;

  show();

  if(!digitalRead(PIN_RIGHT))
  {
    settingLedButton.pin = PIN_RIGHT;
    return;
  }
  if(!digitalRead(PIN_DOWN))
  {
    settingLedButton.pin = PIN_DOWN;
    return;
  }
  if(!digitalRead(PIN_LEFT))
  {
    settingLedButton.pin = PIN_LEFT;
    return;
  }
  if(!digitalRead(PIN_UP))
  {
    settingLedButton.pin = PIN_UP;
    return;
  }
  if(!digitalRead(PIN_P1))
  {
    settingLedButton.pin = PIN_P1;
    return;
  }
  if(!digitalRead(PIN_P2))
  {
    settingLedButton.pin = PIN_P2;
    return;
  }
  if(!digitalRead(PIN_P3))
  {
    settingLedButton.pin = PIN_P3;
    return;
  }
  if(!digitalRead(PIN_P4))
  {
    settingLedButton.pin = PIN_P4;
    return;
  }
  if(!digitalRead(PIN_K1))
  {
    settingLedButton.pin = PIN_K1;
    return;
  }
  if(!digitalRead(PIN_K2))
  {
    settingLedButton.pin = PIN_K2;
    return;
  }
  if(!digitalRead(PIN_K3))
  {
    settingLedButton.pin = PIN_K3;
    return;
  }
  if(!digitalRead(PIN_K4))
  {
    settingLedButton.pin = PIN_K4;
    return;
  }
  if(!digitalRead(PIN_SELECT))
  {
    settingButtonHoldTime += MAIN_LOOP_DELAY;
    if(settingButtonHoldTime >= SETTING_MODE_ENABLE_TIME && settingButtonHoldTime <= SETTING_MODE_ENABLE_TIME + MAIN_LOOP_DELAY)
    {
      show = showShutdownSettingMode;
    }
    return;
  }
  if(settingButtonHoldTime >= SETTING_MODE_ENABLE_TIME)
  {
    kaimana.saveAllColors();
    pollFunction = pollSwitches;
  }
  else if(settingLedButton.isSet())
  {
    const auto led = kaimana.getLED(settingLedButton.pin).led[0];

    kaimana.setALL(BLACK);
    kaimana.setLED(settingLedButton.pin, led.r, led.g, led.b);

    pollFunction = pollSwitchesForSetting;
  }
  show = showStartupSettingMode;
  settingButtonHoldTime = 0;
}

void pollSwitchesForSetting(void)
{
  static int pressedButton = -1;
  constexpr int smallIncreaseAmount = 1;
  constexpr int bigIncreaseAmount = 15;

  kaimana.updateALL();

  if(!digitalRead(PIN_START))
  {
    pressedButton = PIN_START;
    return;
  }
  if(!digitalRead(PIN_SELECT))
  {
    pressedButton = PIN_SELECT;
    return;
  }
  if(pressedButton == PIN_START)
  {
    pressedButton = -1;
    settingLedButton.reset();
    showStartupSettingMode();
    pollFunction = pollSwitchesForSettingSelection;
    return;
  }

  const auto pin = settingLedButton.pin;

  if(pressedButton == PIN_SELECT)
  {
    kaimana.setLED(pin, BLACK);
    kaimana.setColor(pin, BLACK);
    pressedButton = -1;
    return;
  }

  if(settingLedButton.isSetOnMoveSide())
  {
    if(!(digitalRead(PIN_P1) && digitalRead(PIN_K1)))
    {
      pressedButton = PIN_P1;
      return;
    }
    if(!(digitalRead(PIN_P2) && digitalRead(PIN_K2)))
    {
      pressedButton = PIN_P2;
      return;
    }
    if(!(digitalRead(PIN_P3) && digitalRead(PIN_K3)))
    {
      pressedButton = PIN_P3;
      return;
    }

    const int increaseAmount = digitalRead(PIN_P4) && digitalRead(PIN_K4) ? bigIncreaseAmount : smallIncreaseAmount;

    switch (pressedButton)
    {
      case PIN_P1: {
        const auto led = kaimana.getLED(pin).led[0];
        const auto r = (led.r + increaseAmount) % 255;
        kaimana.setLED(pin, r, led.g, led.b);
        kaimana.setColor(pin, r, led.g, led.b);
        break;
      }
      case PIN_P2: {
        const auto led = kaimana.getLED(pin).led[0];
        const auto g = (led.g + increaseAmount) % 255;
        kaimana.setLED(pin, led.r, g, led.b);
        kaimana.setColor(pin, led.r, g, led.b);
        break;
      }
      case PIN_P3: {
        const auto led = kaimana.getLED(pin).led[0];
        const auto b = (led.b + increaseAmount) % 255;
        kaimana.setLED(pin, led.r, led.g, b);
        kaimana.setColor(pin, led.r, led.g, b);
      }
    }
  }
  else
  {
    if(!digitalRead(PIN_LEFT))
    {
      pressedButton = PIN_LEFT;
      return;
    }
    if(!digitalRead(PIN_DOWN))
    {
      pressedButton = PIN_DOWN;
      return;
    }
    if(!digitalRead(PIN_RIGHT))
    {
      pressedButton = PIN_RIGHT;
      return;
    }

    const int increaseAmount = digitalRead(PIN_UP) ? bigIncreaseAmount : smallIncreaseAmount;

    switch (pressedButton)
    {
      case PIN_LEFT: {
        const auto led = kaimana.getLED(pin).led[0];
        const auto r = (led.r + increaseAmount) % 255;
        kaimana.setLED(pin, r, led.g, led.b);
        kaimana.setColor(pin, r, led.g, led.b);
        break;
      }
      case PIN_DOWN: {
        const auto led = kaimana.getLED(pin).led[0];
        const auto g = (led.g + increaseAmount) % 255;
        kaimana.setLED(pin, led.r, g, led.b);
        kaimana.setColor(pin, led.r, g, led.b);
        break;
      }
      case PIN_RIGHT: {
        const auto led = kaimana.getLED(pin).led[0];
        const auto b = (led.b + increaseAmount) % 255;
        kaimana.setLED(pin, led.r, led.g, b);
        kaimana.setColor(pin, led.r, led.g, b);
        break;
      }
    }
  }
  pressedButton = -1;
}

void pollSwitchesForPinLEDSettingSelection(void)
{
    static auto show = showStartupSettingMode;

    show();

    if(!digitalRead(PIN_RIGHT))
    {
        settingPinLEDButton.pin = PIN_RIGHT;
        return;
    }
    if(!digitalRead(PIN_DOWN))
    {
        settingPinLEDButton.pin = PIN_DOWN;
        return;
    }
    if(!digitalRead(PIN_LEFT))
    {
        settingPinLEDButton.pin = PIN_LEFT;
        return;
    }
    if(!digitalRead(PIN_UP))
    {
        settingPinLEDButton.pin = PIN_UP;
        return;
    }
    if(!digitalRead(PIN_P1))
    {
        settingPinLEDButton.pin = PIN_P1;
        return;
    }
    if(!digitalRead(PIN_P2))
    {
        settingPinLEDButton.pin = PIN_P2;
        return;
    }
    if(!digitalRead(PIN_P3))
    {
        settingPinLEDButton.pin = PIN_P3;
        return;
    }
    if(!digitalRead(PIN_P4))
    {
        settingPinLEDButton.pin = PIN_P4;
        return;
    }
    if(!digitalRead(PIN_K1))
    {
        settingPinLEDButton.pin = PIN_K1;
        return;
    }
    if(!digitalRead(PIN_K2))
    {
        settingPinLEDButton.pin = PIN_K2;
        return;
    }
    if(!digitalRead(PIN_K3))
    {
        settingPinLEDButton.pin = PIN_K3;
        return;
    }
    if(!digitalRead(PIN_K4))
    {
        settingPinLEDButton.pin = PIN_K4;
        return;
    }

    if(!digitalRead(PIN_HOME))
    {
        pinLEDSettingButtonHoldTime += MAIN_LOOP_DELAY;
        if(pinLEDSettingButtonHoldTime >= SETTING_MODE_ENABLE_TIME && pinLEDSettingButtonHoldTime <= SETTING_MODE_ENABLE_TIME + MAIN_LOOP_DELAY)
        {
            show = showShutdownSettingMode;
        }
        return;
    }

    if(pinLEDSettingButtonHoldTime >= SETTING_MODE_ENABLE_TIME)
    {
        kaimana.saveAllColors();
        pollFunction = pollSwitches;
    }
    else if(settingPinLEDButton.isSet())
    {
        kaimana.setALL(BLACK);
        kaimana.setLED(settingPinLEDButton.pin, WHITE);

        pollFunction = pollSwitchesForPinLEDSetting;
    }
    show = showStartupSettingMode;
    pinLEDSettingButtonHoldTime = 0;
}

void pollSwitchesForPinLEDSetting(void)
{
    static auto pressedButton = -1;

    kaimana.updateALL();

    if(!digitalRead(PIN_RIGHT))
    {
        pressedButton = PIN_RIGHT;
        return;
    }
    if(!digitalRead(PIN_DOWN))
    {
        pressedButton = PIN_DOWN;
        return;
    }
    if(!digitalRead(PIN_LEFT))
    {
        pressedButton = PIN_LEFT;
        return;
    }
    if(!digitalRead(PIN_UP))
    {
        pressedButton = PIN_UP;
        return;
    }
    if(!digitalRead(PIN_P1))
    {
        pressedButton = PIN_P1;
        return;
    }
    if(!digitalRead(PIN_P2))
    {
        pressedButton = PIN_P2;
        return;
    }
    if(!digitalRead(PIN_P3))
    {
        pressedButton = PIN_P3;
        return;
    }
    if(!digitalRead(PIN_P4))
    {
        pressedButton = PIN_P4;
        return;
    }
    if(!digitalRead(PIN_K1))
    {
        pressedButton = PIN_K1;
        return;
    }
    if(!digitalRead(PIN_K2))
    {
        pressedButton = PIN_K2;
        return;
    }
    if(!digitalRead(PIN_K3))
    {
        pressedButton = PIN_K3;
        return;
    }
    if(!digitalRead(PIN_K4))
    {
        pressedButton = PIN_K4;
        return;
    }

    if(pressedButton != -1)
    {
        const auto led1 = kaimana.getLED(settingPinLEDButton.pin);
        const auto led2 = kaimana.getLED(pressedButton);
        kaimana.setPinLEDMapping(settingPinLEDButton.pin, led2.index);
        kaimana.setPinLEDMapping(pressedButton, led1.index);

        kaimana.setALL(BLACK);
        pressedButton = -1;
        settingPinLEDButton.reset();
        pollFunction = pollSwitchesForPinLEDSettingSelection;
        return;
    }

    pressedButton = -1;
}
