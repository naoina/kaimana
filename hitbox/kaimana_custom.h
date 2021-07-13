//  kaimana_local.h
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
//  Kaimana localization file based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//

#ifndef __kaimana_local_h__
#define __kaimana_local_h__

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "kaimana.h"

// Kaimana J2 RGB LED has 2 LEDs.
#define  LED_P1_1      16
#define  LED_P2_1      14
#define  LED_P3_1      12
#define  LED_P4_1      10
#define  LED_K1_1      2
#define  LED_K2_1      4
#define  LED_K3_1      6
#define  LED_K4_1      8
#define  LED_LEFT_1    22
#define  LED_DOWN_1    20
#define  LED_RIGHT_1   18
#define  LED_UP_1      0
#define  LED_HOME_1    24
#define  LED_GUIDE_1   26
#define  LED_SELECT_1  28
#define  LED_BACK_1    30
#define  LED_START_1   32
#define  LED_P1_2      (LED_P1_1 + 1)
#define  LED_P2_2      (LED_P2_1 + 1)
#define  LED_P3_2      (LED_P3_1 + 1)
#define  LED_P4_2      (LED_P4_1 + 1)
#define  LED_K1_2      (LED_K1_1 + 1)
#define  LED_K2_2      (LED_K2_1 + 1)
#define  LED_K3_2      (LED_K3_1 + 1)
#define  LED_K4_2      (LED_K4_1 + 1)
#define  LED_LEFT_2    (LED_LEFT_1 + 1)
#define  LED_DOWN_2    (LED_DOWN_1 + 1)
#define  LED_RIGHT_2   (LED_RIGHT_1 + 1)
#define  LED_UP_2      (LED_UP_1 + 1)
#define  LED_HOME_2    (LED_HOME_1 + 1)
#define  LED_GUIDE_2   (LED_GUIDE_1 + 1)
#define  LED_SELECT_2  (LED_SELECT_1 + 1)
#define  LED_BACK_2    (LED_BACK_1 + 1)
#define  LED_START_2   (LED_START_1 + 1)

// maximum number of LEDs attached to Kaimana board
// best to leave value untouched at 12 unless you understand why
#define  LED_COUNT   24

#define  COLOR_LED_P1_1      PURPLE
#define  COLOR_LED_P1_2      PURPLE
#define  COLOR_LED_P2_1      PURPLE
#define  COLOR_LED_P2_2      PURPLE
#define  COLOR_LED_P3_1      PURPLE
#define  COLOR_LED_P3_2      PURPLE
#define  COLOR_LED_P4_1      PURPLE
#define  COLOR_LED_P4_2      PURPLE
#define  COLOR_LED_K1_1      PURPLE
#define  COLOR_LED_K1_2      PURPLE
#define  COLOR_LED_K2_1      PURPLE
#define  COLOR_LED_K2_2      PURPLE
#define  COLOR_LED_K3_1      PURPLE
#define  COLOR_LED_K3_2      PURPLE
#define  COLOR_LED_K4_1      PURPLE
#define  COLOR_LED_K4_2      PURPLE
#define  COLOR_LED_LEFT_1    WHITE
#define  COLOR_LED_LEFT_2    WHITE
#define  COLOR_LED_DOWN_1    WHITE
#define  COLOR_LED_DOWN_2    WHITE
#define  COLOR_LED_RIGHT_1   WHITE
#define  COLOR_LED_RIGHT_2   WHITE
#define  COLOR_LED_UP_1      PINK
#define  COLOR_LED_UP_2      PINK

// general definitions for delays and other customizable features
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  BOOT_COLOR_DELAY         250    // value in miliseconds
#define  BOOT_COMPLETE_DELAY      500    // value in miliseconds
#define  MAIN_LOOP_DELAY           16    // value in miliseconds - used main loop
#define  IDLE_TIMEOUT_SECONDS      30    // value in seconds - normally 60 or 30 seconds but set very short for testing


// definitions of RGB values use by random color generator: setLEDRandomColor(int)
#define  COLOR_RANDOM_1    127,220,000    // lime green
#define  COLOR_RANDOM_2    127,000,220    // purple
#define  COLOR_RANDOM_3    000,220,220    // blue
#define  COLOR_RANDOM_4    000,255,127    // cyan
#define  COLOR_RANDOM_5    000,127,255    // cobalt blue
#define  COLOR_RANDOM_6    255,000,000    // red
#define  COLOR_RANDOM_7    220,127,000    // orange
#define  COLOR_RANDOM_8    220,000,127    // magenta

#endif
