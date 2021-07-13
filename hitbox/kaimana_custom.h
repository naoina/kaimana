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


// uncomment exactly one of the _LED_ORDER_*_ choices below or make your own 
// based on the order you have your LEDs connected to the Kaimana board
//
#define  _LED_ORDER_DEFAULT_  true
//#define  _LED_ORDER_JWYDER_   true


#ifdef _LED_ORDER_DEFAULT_
  // Map function names to default LED index numbers
  // specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
  // change or expand as needed
  //
  //   KAIMANA->LED_JOY->LED_HOME->LED_SELECT->LED_START->LED_P1->LED-P2->LED_P3->LED-P4->LED_K1->LED-K2->LED_K3->LED-K4
  //
  #define  LED_JOY     0
  #define  LED_HOME    1
  #define  LED_GUIDE   1
  #define  LED_SELECT  2
  #define  LED_BACK    2
  #define  LED_START   3
  #define  LED_P1      4
  #define  LED_P2      5
  #define  LED_P3      6
  #define  LED_P4      7
  #define  LED_K1      8
  #define  LED_K2      9
  #define  LED_K3      10
  #define  LED_K4      11
#endif


#ifdef _LED_ORDER_JWYDER_
  // Map function names to LED index numbers 
  // example for just K4-K1 and P1-P4 are connected first to the Kaimana board
  // submitted by jwyder
  //
  //   KAIMANA->LED-K4->LED_K3->LED_K2->LED_K1->LED-P1->LED_P2->LED-P3->LED_P4->LED_JOY->LED_HOME->LED_SELECT->LED_START
  //
  #define  LED_K4      0
  #define  LED_K3      1
  #define  LED_K2      2
  #define  LED_K1      3
  #define  LED_P1      4
  #define  LED_P2      5
  #define  LED_P3      6
  #define  LED_P4      7
  #define  LED_JOY     8
  #define  LED_HOME    9
  #define  LED_GUIDE   9
  #define  LED_SELECT  10
  #define  LED_BACK    10
  #define  LED_START   11
#endif


// maximum number of LEDs attached to Kaimana board
// best to leave value untouched at 12 unless you understand why
#define  LED_COUNT   12


// general definitions for delays and other customizable features
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  BOOT_COLOR_DELAY         250    // value in miliseconds
#define  BOOT_COMPLETE_DELAY      500    // value in miliseconds
#define  MAIN_LOOP_DELAY           50    // value in miliseconds - used main loop
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
