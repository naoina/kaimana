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
#include "kaimana.h"
#include "kaimana_custom.h"
// local function declarations
int  pollSwitches(void);
void showStartup(void);
void setLEDRandomColor(int index);
// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;
// the setup routine runs first and once each time power is applied to the Kaimana board
void setup()
{
  // light up all leds at boot to demonstrate everything is functional
  showStartup();
}
// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop()
{
  unsigned long  ulTimeout;
  // initialize timeout value to now + some seconds
  ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
  // infinite loop of read switches, update LEDs and idle animation when necessary
  while(true)
  {
    // active -- poll switches and update leds
    if( pollSwitches() != 0 )
    {
        // some switches were active so reset idle timeout to now + some seconds
        ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
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
  kaimana.setALL( BLACK );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( RED );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( GREEN );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( BLUE );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( BLACK );
  delay( BOOT_COMPLETE_DELAY );
}
// set LED to one of 8 predefined colors selected at random
//
void setLEDRandomColor(int index)
{
  switch(random(1,8))    // pick a random color between 1 and 8
  {
    case 1:
      kaimana.setLED(index, COLOR_RANDOM_1);
      break;
    case 2:
      kaimana.setLED(index, COLOR_RANDOM_2);
      break;
    case 3:
      kaimana.setLED(index, COLOR_RANDOM_3);
      break;
    case 4:
      kaimana.setLED(index, COLOR_RANDOM_4);
      break;
    case 5:
      kaimana.setLED(index, COLOR_RANDOM_5);
      break;
    case 6:
      kaimana.setLED(index, COLOR_RANDOM_6);
      break;
    case 7:
      kaimana.setLED(index, COLOR_RANDOM_7);
      break;
    case 8:
      kaimana.setLED(index, COLOR_RANDOM_8);
      break;
    default:   // any undefined value so discard data and set led to BLACK
      kaimana.setLED(index, BLACK);
      break;
  }
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
