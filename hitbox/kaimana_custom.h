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

// basic color definitions with various R,G,B values
// generic (may  want to prefix with COLOR_* to localize further)
#define  BLACK      000,000,000
#define  RED        255,000,000
#define  GREEN      000,255,000
#define  YELLOW     255,255,000
#define  BLUE       000,000,255
#define  PURPLE     255,000,255
#define  CYAN       000,255,255
#define  WHITE      255,255,255
#define  DARK_WHITE 16,16,16
#define  PINK       166,15,36

#define  COLOR_LED_P1_1      WHITE
#define  COLOR_LED_P1_2      WHITE
#define  COLOR_LED_P2_1      WHITE
#define  COLOR_LED_P2_2      WHITE
#define  COLOR_LED_P3_1      WHITE
#define  COLOR_LED_P3_2      WHITE
#define  COLOR_LED_P4_1      WHITE
#define  COLOR_LED_P4_2      WHITE
#define  COLOR_LED_K1_1      WHITE
#define  COLOR_LED_K1_2      WHITE
#define  COLOR_LED_K2_1      WHITE
#define  COLOR_LED_K2_2      WHITE
#define  COLOR_LED_K3_1      WHITE
#define  COLOR_LED_K3_2      WHITE
#define  COLOR_LED_K4_1      WHITE
#define  COLOR_LED_K4_2      WHITE
#define  COLOR_LED_LEFT_1    DARK_WHITE
#define  COLOR_LED_LEFT_2    DARK_WHITE
#define  COLOR_LED_DOWN_1    DARK_WHITE
#define  COLOR_LED_DOWN_2    DARK_WHITE
#define  COLOR_LED_RIGHT_1   DARK_WHITE
#define  COLOR_LED_RIGHT_2   DARK_WHITE
#define  COLOR_LED_UP_1      DARK_WHITE
#define  COLOR_LED_UP_2      DARK_WHITE

// general definitions for delays and other customizable features
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  BOOT_COLOR_DELAY          250    // value in miliseconds
#define  BOOT_COMPLETE_DELAY      2000    // value in miliseconds
#define  MAIN_LOOP_DELAY            16    // value in miliseconds - used main loop
#define  TOURNEY_MODE_ENABLE_TIME 3000    // value in milliseconds

#endif
