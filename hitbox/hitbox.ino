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
void showStartup(void);
// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;

bool tourneyMode = true;
int tourneyButtonHoldTime = 0;

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
    if(tourneyMode)
    {
        pollSwitchesForTourneyMode();
    }
    else
    {
        // active -- poll switches and update leds
        pollSwitches();
    }
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
  kaimana.setLED(LED_P1_1, COLOR_LED_P1_1);
  kaimana.setLED(LED_P1_2, COLOR_LED_P1_2);
  kaimana.setLED(LED_P2_1, COLOR_LED_P2_1);
  kaimana.setLED(LED_P2_2, COLOR_LED_P2_2);
  kaimana.setLED(LED_P3_1, COLOR_LED_P3_1);
  kaimana.setLED(LED_P3_2, COLOR_LED_P3_2);
  kaimana.setLED(LED_P4_1, COLOR_LED_P4_1);
  kaimana.setLED(LED_P4_2, COLOR_LED_P4_2);
  kaimana.setLED(LED_K1_1, COLOR_LED_K1_1);
  kaimana.setLED(LED_K1_2, COLOR_LED_K1_2);
  kaimana.setLED(LED_K2_1, COLOR_LED_K2_1);
  kaimana.setLED(LED_K2_2, COLOR_LED_K2_2);
  kaimana.setLED(LED_K3_1, COLOR_LED_K3_1);
  kaimana.setLED(LED_K3_2, COLOR_LED_K3_2);
  kaimana.setLED(LED_K4_1, COLOR_LED_K4_1);
  kaimana.setLED(LED_K4_2, COLOR_LED_K4_2);
  kaimana.setLED(LED_LEFT_1, COLOR_LED_LEFT_1);
  kaimana.setLED(LED_LEFT_2, COLOR_LED_LEFT_2);
  kaimana.setLED(LED_DOWN_1, COLOR_LED_DOWN_1);
  kaimana.setLED(LED_DOWN_2, COLOR_LED_DOWN_2);
  kaimana.setLED(LED_RIGHT_1, COLOR_LED_RIGHT_1);
  kaimana.setLED(LED_RIGHT_2, COLOR_LED_RIGHT_2);
  kaimana.setLED(LED_UP_1, COLOR_LED_UP_1);
  kaimana.setLED(LED_UP_2, COLOR_LED_UP_2);
  kaimana.updateALL();
  delay(BOOT_COMPLETE_DELAY);
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
        kaimana.setLED(LED_RIGHT_1, COLOR_LED_RIGHT_1);
        iLED[LED_RIGHT_1] = true;
    }
    if(!iLED[LED_RIGHT_2])
    {
        kaimana.setLED(LED_RIGHT_2, COLOR_LED_RIGHT_2);
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
        kaimana.setLED(LED_DOWN_1, COLOR_LED_DOWN_1);
        iLED[LED_DOWN_1] = true;
    }
    if(!iLED[LED_DOWN_2])
    {
        kaimana.setLED(LED_DOWN_2, COLOR_LED_DOWN_2);
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
        kaimana.setLED(LED_LEFT_1, COLOR_LED_LEFT_1);
        iLED[LED_LEFT_1] = true;
    }
    if(!iLED[LED_LEFT_2])
    {
        kaimana.setLED(LED_LEFT_2, COLOR_LED_LEFT_2);
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
        kaimana.setLED(LED_UP_1, COLOR_LED_UP_1);
        iLED[LED_UP_1] = true;
    }
    if(!iLED[LED_UP_2])
    {
        kaimana.setLED(LED_UP_2, COLOR_LED_UP_2);
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
      kaimana.setLED(LED_P1_1, COLOR_LED_P1_1);
      iLED[LED_P1_1] = true;
    }
    if(!iLED[LED_P1_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P1_2, COLOR_LED_P1_2);
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
      kaimana.setLED(LED_P2_1, COLOR_LED_P2_1);
      iLED[LED_P2_1] = true;
    }
    if(!iLED[LED_P2_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P2_2, COLOR_LED_P2_2);
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
      kaimana.setLED(LED_P3_1, COLOR_LED_P3_1);
      iLED[LED_P3_1] = true;
    }
    if(!iLED[LED_P3_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P3_2, COLOR_LED_P3_2);
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
      kaimana.setLED(LED_P4_1, COLOR_LED_P4_1);
      iLED[LED_P4_1] = true;
    }
    if(!iLED[LED_P4_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P4_2, COLOR_LED_P4_2);
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
      kaimana.setLED(LED_K1_1, COLOR_LED_K1_1);
      iLED[LED_K1_1] = true;
    }
    if(!iLED[LED_K1_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K1_2, COLOR_LED_K1_2);
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
      kaimana.setLED(LED_K2_1, COLOR_LED_K2_1);
      iLED[LED_K2_1] = true;
    }
    if(!iLED[LED_K2_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K2_2, COLOR_LED_K2_2);
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
      kaimana.setLED(LED_K3_1, COLOR_LED_K3_1);
      iLED[LED_K3_1] = true;
    }
    if(!iLED[LED_K3_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K3_2, COLOR_LED_K3_2);
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
      kaimana.setLED(LED_K4_1, COLOR_LED_K4_1);
      iLED[LED_K4_1] = true;
    }
    if(!iLED[LED_K4_2])
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K4_2, COLOR_LED_K4_2);
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
      tourneyMode = true;
    }
    tourneyButtonHoldTime = 0;
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
      kaimana.updateALL();
    }
  }
  else
  {
    if(tourneyButtonHoldTime >= TOURNEY_MODE_ENABLE_TIME)
    {
        tourneyMode = false;
    }
    tourneyButtonHoldTime = 0;
  }
}
