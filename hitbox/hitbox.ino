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
int  pollSwitches(void);
void pollSwitchesForTourneyMode(void);
void pollSwitchesForSettingSelection(void);
void pollSwitchesForSetting(void);
void showStartup(void);
// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;

auto pollFunction = pollSwitchesForTourneyMode;
int tourneyButtonHoldTime = 0;
int settingButtonHoldTime = 0;
struct SettingLedButton {
    int first;
    int second;

    SettingLedButton()
    {
      reset();
    }

    bool isSet(void)
    {
      return first != -1 && second != -1;
    }

    void reset(void)
    {
      first = -1;
      second = -1;
    }

    bool isSetOnMoveSide(void)
    {
      switch (first)
      {
        case LED_RIGHT_1:
        case LED_RIGHT_2:
        case LED_DOWN_1:
        case LED_DOWN_2:
        case LED_LEFT_1:
        case LED_LEFT_2:
        case LED_UP_1:
        case LED_UP_2:
          return true;
      }
      return false;
    }
} settingLedButton;

// the setup routine runs first and once each time power is applied to the Kaimana board
void setup()
{
  // do nothing.
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
  kaimana.setLED(LED_P1_1);
  kaimana.setLED(LED_P1_2);
  kaimana.setLED(LED_P2_1);
  kaimana.setLED(LED_P2_2);
  kaimana.setLED(LED_P3_1);
  kaimana.setLED(LED_P3_2);
  kaimana.setLED(LED_P4_1);
  kaimana.setLED(LED_P4_2);
  kaimana.setLED(LED_K1_1);
  kaimana.setLED(LED_K1_2);
  kaimana.setLED(LED_K2_1);
  kaimana.setLED(LED_K2_2);
  kaimana.setLED(LED_K3_1);
  kaimana.setLED(LED_K3_2);
  kaimana.setLED(LED_K4_1);
  kaimana.setLED(LED_K4_2);
  kaimana.setLED(LED_LEFT_1);
  kaimana.setLED(LED_LEFT_2);
  kaimana.setLED(LED_DOWN_1);
  kaimana.setLED(LED_DOWN_2);
  kaimana.setLED(LED_RIGHT_1);
  kaimana.setLED(LED_RIGHT_2);
  kaimana.setLED(LED_UP_1);
  kaimana.setLED(LED_UP_2);
  kaimana.updateALL();
  delay(BOOT_COMPLETE_DELAY);
  kaimana.setALL(BLACK);
}

void showStartupSettingMode()
{
  kaimana.setLED(LED_P1_1);
  kaimana.setLED(LED_P1_2);
  kaimana.setLED(LED_P2_1);
  kaimana.setLED(LED_P2_2);
  kaimana.setLED(LED_P3_1);
  kaimana.setLED(LED_P3_2);
  kaimana.setLED(LED_P4_1);
  kaimana.setLED(LED_P4_2);
  kaimana.setLED(LED_K1_1);
  kaimana.setLED(LED_K1_2);
  kaimana.setLED(LED_K2_1);
  kaimana.setLED(LED_K2_2);
  kaimana.setLED(LED_K3_1);
  kaimana.setLED(LED_K3_2);
  kaimana.setLED(LED_K4_1);
  kaimana.setLED(LED_K4_2);
  kaimana.setLED(LED_LEFT_1);
  kaimana.setLED(LED_LEFT_2);
  kaimana.setLED(LED_DOWN_1);
  kaimana.setLED(LED_DOWN_2);
  kaimana.setLED(LED_RIGHT_1);
  kaimana.setLED(LED_RIGHT_2);
  kaimana.setLED(LED_UP_1);
  kaimana.setLED(LED_UP_2);
  kaimana.updateALL();
}

void showShutdownSettingMode()
{
  kaimana.setALL(BLACK);
}

int pollSwitches(void)
{
  static int  iLED[LED_COUNT];
  static int  iActiveSwitchCount;
  static int  i;
  static int  j;
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;
  // reset LED status
  if (firsttime == 1)
  {
    for(i=0;i<LED_COUNT;++i)
    {
      iLED[i] = false;
      firsttime = 0;
    }
  }
  // clear results for switch activity
  switchActivity = ATTACK_NONE;
  if(!digitalRead(PIN_RIGHT))
  {
    if(!iLED[LED_RIGHT_1])
    {
        kaimana.setLED(LED_RIGHT_1);
        iLED[LED_RIGHT_1] = true;
    }
    if(!iLED[LED_RIGHT_2])
    {
        kaimana.setLED(LED_RIGHT_2);
        iLED[LED_RIGHT_2] = true;
    }
  }
  else
  {
    kaimana.setLED(LED_RIGHT_1, BLACK);
    kaimana.setLED(LED_RIGHT_2, BLACK);
    iLED[LED_RIGHT_1] = false;
    iLED[LED_RIGHT_2] = false;
  }
  if(!digitalRead(PIN_DOWN))
  {
    if(!iLED[LED_DOWN_1])
    {
        kaimana.setLED(LED_DOWN_1);
        iLED[LED_DOWN_1] = true;
    }
    if(!iLED[LED_DOWN_2])
    {
        kaimana.setLED(LED_DOWN_2);
        iLED[LED_DOWN_2] = true;
    }
  }
  else
  {
    kaimana.setLED(LED_DOWN_1, BLACK);
    kaimana.setLED(LED_DOWN_2, BLACK);
    iLED[LED_DOWN_1] = false;
    iLED[LED_DOWN_2] = false;
  }
  if(!digitalRead(PIN_LEFT))
  {
    if(!iLED[LED_LEFT_1])
    {
        kaimana.setLED(LED_LEFT_1);
        iLED[LED_LEFT_1] = true;
    }
    if(!iLED[LED_LEFT_2])
    {
        kaimana.setLED(LED_LEFT_2);
        iLED[LED_LEFT_2] = true;
    }
  }
  else
  {
    kaimana.setLED(LED_LEFT_1, BLACK);
    kaimana.setLED(LED_LEFT_2, BLACK);
    iLED[LED_LEFT_1] = false;
    iLED[LED_LEFT_2] = false;
  }
  if(!digitalRead(PIN_UP))
  {
    if(!iLED[LED_UP_1])
    {
        kaimana.setLED(LED_UP_1);
        iLED[LED_UP_1] = true;
    }
    if(!iLED[LED_UP_2])
    {
        kaimana.setLED(LED_UP_2);
        iLED[LED_UP_2] = true;
    }
  }
  else
  {
    kaimana.setLED(LED_UP_1, BLACK);
    kaimana.setLED(LED_UP_2, BLACK);
    iLED[LED_UP_1] = false;
    iLED[LED_UP_2] = false;
  }
  // test switch and set LED based on result
  if(!digitalRead(PIN_P1))
  {
    switchActivity |= ATTACK_P1;
    // switch is active
    if(!iLED[LED_P1_1])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P1_1);
      iLED[LED_P1_1] = true;
    }
    if(!iLED[LED_P1_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P1_2);
      iLED[LED_P1_2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P1_1, BLACK);
      kaimana.setLED(LED_P1_2, BLACK);
      iLED[LED_P1_1] = false;
      iLED[LED_P1_2] = false;
  }
  // test switch and set LED based on result
  if(!digitalRead(PIN_P2))
  {
    switchActivity |= ATTACK_P2;
    // switch is active
    if(!iLED[LED_P2_1])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P2_1);
      iLED[LED_P2_1] = true;
    }
    if(!iLED[LED_P2_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P2_2);
      iLED[LED_P2_2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P2_1, BLACK);
      kaimana.setLED(LED_P2_2, BLACK);
      iLED[LED_P2_1] = false;
      iLED[LED_P2_2] = false;
  }
  // test switch and set LED based on result
  if(!digitalRead(PIN_P3))
  {
    switchActivity |= ATTACK_P3;
    // switch is active
    if(!iLED[LED_P3_1])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P3_1);
      iLED[LED_P3_1] = true;
    }
    if(!iLED[LED_P3_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P3_2);
      iLED[LED_P3_2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P3_1, BLACK);
      kaimana.setLED(LED_P3_2, BLACK);
      iLED[LED_P3_1] = false;
      iLED[LED_P3_2] = false;
  }
  // test switch and set LED based on result
  if(!digitalRead(PIN_P4))
  {
    switchActivity |= ATTACK_P4;
    // switch is active
    if(!iLED[LED_P4_1])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P4_1);
      iLED[LED_P4_1] = true;
    }
    if(!iLED[LED_P4_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P4_2);
      iLED[LED_P4_2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P4_1, BLACK);
      kaimana.setLED(LED_P4_2, BLACK);
      iLED[LED_P4_1] = false;
      iLED[LED_P4_2] = false;
  }
  // test switch and set LED based on result
  if(!digitalRead(PIN_K1))
  {
    switchActivity |= ATTACK_K1;
    // switch is active
    if(!iLED[LED_K1_1])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K1_1);
      iLED[LED_K1_1] = true;
    }
    if(!iLED[LED_K1_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K1_2);
      iLED[LED_K1_2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K1_1, BLACK);
      kaimana.setLED(LED_K1_2, BLACK);
      iLED[LED_K1_1] = false;
      iLED[LED_K1_2] = false;
  }
  // test switch and set LED based on result
  if(!digitalRead(PIN_K2))
  {
    switchActivity |= ATTACK_K2;
    // switch is active
    if(!iLED[LED_K2_1])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K2_1);
      iLED[LED_K2_1] = true;
    }
    if(!iLED[LED_K2_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K2_2);
      iLED[LED_K2_2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K2_1, BLACK);
      kaimana.setLED(LED_K2_2, BLACK);
      iLED[LED_K2_1] = false;
      iLED[LED_K2_2] = false;
  }
  // test switch and set LED based on result
  if(!digitalRead(PIN_K3))
  {
    switchActivity |= ATTACK_K3;
    // switch is active
    if(!iLED[LED_K3_1])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K3_1);
      iLED[LED_K3_1] = true;
    }
    if(!iLED[LED_K3_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K3_2);
      iLED[LED_K3_2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K3_1, BLACK);
      kaimana.setLED(LED_K3_2, BLACK);
      iLED[LED_K3_1] = false;
      iLED[LED_K3_2] = false;
  }
  // test switch and set LED based on result
  if(!digitalRead(PIN_K4))
  {
    switchActivity |= ATTACK_K4;
    // switch is active
    if(!iLED[LED_K4_1])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K4_1);
      iLED[LED_K4_1] = true;
    }
    if(!iLED[LED_K4_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K4_2);
      iLED[LED_K4_2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K4_1, BLACK);
      kaimana.setLED(LED_K4_2, BLACK);
      iLED[LED_K4_1] = false;
      iLED[LED_K4_2] = false;
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

  // zero active switch counter (note: 4 way joystick counts as 1)
  iActiveSwitchCount = 0;
  // set LED color based on switch
  for(i=0;i<LED_COUNT;++i)
  {
    if(iLED[i] == true)
      ++iActiveSwitchCount;
  }
  // update the leds with new/current colors in the array
  kaimana.updateALL();
  // return number of active switches
  return(iActiveSwitchCount);
}

void pollSwitchesForTourneyMode(void)
{
  if(!digitalRead(PIN_START))
  {
    tourneyButtonHoldTime += MAIN_LOOP_DELAY;
    // Do animations a once when moves to non-tourney mode.
    if(tourneyButtonHoldTime >= TOURNEY_MODE_ENABLE_TIME && tourneyButtonHoldTime <= TOURNEY_MODE_ENABLE_TIME + MAIN_LOOP_DELAY)
    {
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
    settingLedButton.first = LED_RIGHT_1;
    settingLedButton.second = LED_RIGHT_2;
    return;
  }
  if(!digitalRead(PIN_DOWN))
  {
    settingLedButton.first = LED_DOWN_1;
    settingLedButton.second = LED_DOWN_2;
    return;
  }
  if(!digitalRead(PIN_LEFT))
  {
    settingLedButton.first = LED_LEFT_1;
    settingLedButton.second = LED_LEFT_2;
    return;
  }
  if(!digitalRead(PIN_UP))
  {
    settingLedButton.first = LED_UP_1;
    settingLedButton.second = LED_UP_2;
    return;
  }
  if(!digitalRead(PIN_P1))
  {
    settingLedButton.first = LED_P1_1;
    settingLedButton.second = LED_P1_2;
    return;
  }
  if(!digitalRead(PIN_P2))
  {
    settingLedButton.first = LED_P2_1;
    settingLedButton.second = LED_P2_2;
    return;
  }
  if(!digitalRead(PIN_P3))
  {
    settingLedButton.first = LED_P3_1;
    settingLedButton.second = LED_P3_2;
    return;
  }
  if(!digitalRead(PIN_P4))
  {
    settingLedButton.first = LED_P4_1;
    settingLedButton.second = LED_P4_2;
    return;
  }
  if(!digitalRead(PIN_K1))
  {
    settingLedButton.first = LED_K1_1;
    settingLedButton.second = LED_K1_2;
    return;
  }
  if(!digitalRead(PIN_K2))
  {
    settingLedButton.first = LED_K2_1;
    settingLedButton.second = LED_K2_2;
    return;
  }
  if(!digitalRead(PIN_K3))
  {
    settingLedButton.first = LED_K3_1;
    settingLedButton.second = LED_K3_2;
    return;
  }
  if(!digitalRead(PIN_K4))
  {
    settingLedButton.first = LED_K4_1;
    settingLedButton.second = LED_K4_2;
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
    pollFunction = pollSwitches;
  }
  else if(settingLedButton.isSet())
  {
    const int indexes[2] = {settingLedButton.first, settingLedButton.second};
    RGB_t leds[2] = {
      kaimana.getLED(indexes[0]),
      kaimana.getLED(indexes[1]),
    };

    kaimana.setALL(BLACK);

    for(auto i = 0; i < 2; i++)
    {
      const auto led = leds[i];
      kaimana.setLED(indexes[i], led.r, led.g, led.b);
    }
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
    kaimana.saveAllColors();
    showStartupSettingMode();
    pollFunction = pollSwitchesForSettingSelection;
    return;
  }

  const int indexes[2] = {settingLedButton.first, settingLedButton.second};

  if(pressedButton == PIN_SELECT)
  {
    for(const auto& index: indexes)
    {
      kaimana.setLED(index, BLACK);
      kaimana.setColor(index, BLACK);
      pressedButton = -1;
    }
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
      case PIN_P1:
        for(const auto& index: indexes)
        {
          const auto led = kaimana.getLED(index);
          const auto r = (led.r + increaseAmount) % 255;
          kaimana.setLED(index, r, led.g, led.b);
          kaimana.setColor(index, r, led.g, led.b);
        }
        break;
      case PIN_P2:
        for(const auto& index: indexes)
        {
          const auto led = kaimana.getLED(index);
          const auto g = (led.g + increaseAmount) % 255;
          kaimana.setLED(index, led.r, g, led.b);
          kaimana.setColor(index, led.r, g, led.b);
        }
        break;
      case PIN_P3:
        for(const auto& index: indexes)
        {
          const auto led = kaimana.getLED(index);
          const auto b = (led.b + increaseAmount) % 255;
          kaimana.setLED(index, led.r, led.g, b);
          kaimana.setColor(index, led.r, led.g, b);
        }
        break;
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
      case PIN_LEFT:
        for(const auto& index: indexes)
        {
          const auto led = kaimana.getLED(index);
          const auto r = (led.r + increaseAmount) % 255;
          kaimana.setLED(index, r, led.g, led.b);
          kaimana.setColor(index, r, led.g, led.b);
        }
        break;
      case PIN_DOWN:
        for(const auto& index: indexes)
        {
          const auto led = kaimana.getLED(index);
          const auto g = (led.g + increaseAmount) % 255;
          kaimana.setLED(index, led.r, g, led.b);
          kaimana.setColor(index, led.r, g, led.b);
        }
        break;
      case PIN_RIGHT:
        for(const auto& index: indexes)
        {
          const auto led = kaimana.getLED(index);
          const auto b = (led.b + increaseAmount) % 255;
          kaimana.setLED(index, led.r, led.g, b);
          kaimana.setColor(index, led.r, led.g, b);
        }
        break;
    }
  }
  pressedButton = -1;
}
