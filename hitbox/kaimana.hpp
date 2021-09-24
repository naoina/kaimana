//  kaimana.cpp
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
//  Kaimana class based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "Arduino.h"
#include "kaimana_custom.h"


// Map function names to arduino leonardo atmega32u4 digital pin numbers
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  PIN_DOWN    11
#define  PIN_UP      18
#define  PIN_LEFT    19
#define  PIN_RIGHT   20
#define  PIN_HOME    8
#define  PIN_GUIDE   8
#define  PIN_SELECT  9
#define  PIN_BACK    9
#define  PIN_START   10
#define  PIN_P1      3
#define  PIN_P2      2
#define  PIN_P3      0
#define  PIN_P4      1
#define  PIN_K1      4
#define  PIN_K2      21
#define  PIN_K3      12
#define  PIN_K4      6
//
#define  PIN_LED     23


// Map function names to binary input masks on atmega32u4 digital pin numbers
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  ATTACK_UP      0x0800UL
#define  ATTACK_DOWN    0x0400UL
#define  ATTACK_LEFT    0x0200UL
#define  ATTACK_RIGHT   0x0100UL
#define  ATTACK_K4      0x0080UL
#define  ATTACK_K3      0x0040UL
#define  ATTACK_K2      0x0020UL
#define  ATTACK_K1      0x0010UL
#define  ATTACK_P4      0x0008UL
#define  ATTACK_P3      0x0004UL
#define  ATTACK_P2      0x0002UL
#define  ATTACK_P1      0x0001UL
#define  ATTACK_NONE    0x0000UL
#define  ATTACK_FALSE   0xFFFFUL

// if this is changed then Kaimana::switchHistoryTest must also be revised
#define SWITCH_HISTORY_MAX  16


// RGB value structure.
typedef struct __attribute__ ((__packed__)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_t;

// Kaimana J2 RGB LED has 2 LEDs.
typedef struct __attribute__ ((__packed__)) {
    RGB_t   led[2];
    uint8_t index;
} LED_t;


// table of switch pin numbers
constexpr unsigned char switchPins[] = { PIN_DOWN, PIN_UP, PIN_LEFT, PIN_RIGHT, PIN_P1, PIN_P2, PIN_P3, PIN_P4, PIN_K1, PIN_K2, PIN_K3, PIN_K4/*, PIN_START, PIN_SELECT, PIN_HOME*/ };
constexpr uint8_t SWITCH_COUNT = sizeof(switchPins) / sizeof(switchPins[0]);

// define the Kaimana class
//
class Kaimana
{
  private:
    // declare RGB array for 15 buttons --> 12 LEDs
    // specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
    RGB_t    _led[LED_COUNT];
    LED_t    _color[SWITCH_COUNT];
    uint8_t  _pin_color_index[PIN_LED];
    uint16_t _switchHistory[SWITCH_HISTORY_MAX];

    constexpr int getEEPROMAddress(int index)
    {
      return index * sizeof(LED_t);
    }

    constexpr int getPinColorIndex(const int pin)
    {
        return _pin_color_index[pin];
    }

  public:
    Kaimana(void)
    {
      // Kaimana Class Initialziation

      // set arduino led driver pin to output and low
      pinMode( PIN_LED, OUTPUT );
      digitalWrite( PIN_LED, LOW );

      // initialize random number seed with analog input #4 on port F1
      randomSeed(analogRead(4));

      // set arduino pins for input and enable internal pull up resistors
      pinMode( PIN_DOWN,   INPUT_PULLUP );
      pinMode( PIN_UP,     INPUT_PULLUP );
      pinMode( PIN_LEFT,   INPUT_PULLUP );
      pinMode( PIN_RIGHT,  INPUT_PULLUP );
      pinMode( PIN_HOME,   INPUT_PULLUP );    // HOME = GUIDE
      pinMode( PIN_SELECT, INPUT_PULLUP );    // SELECT = BACK 
      pinMode( PIN_START,  INPUT_PULLUP );
      pinMode( PIN_P1,     INPUT_PULLUP );
      pinMode( PIN_P2,     INPUT_PULLUP );
      pinMode( PIN_P3,     INPUT_PULLUP );
      pinMode( PIN_P4,     INPUT_PULLUP );
      pinMode( PIN_K1,     INPUT_PULLUP );
      pinMode( PIN_K2,     INPUT_PULLUP );
      pinMode( PIN_K3,     INPUT_PULLUP );
      pinMode( PIN_K4,     INPUT_PULLUP );

      for(auto i = 0; i < SWITCH_COUNT; i++)
      {
          _pin_color_index[switchPins[i]] = i;
      }

      EEPROM.get(0, _color);

      // initialize Switch History
      switchHistoryClear();
    }

    LED_t getLED(int pin)
    {
        return _color[getPinColorIndex(pin)];
    }

    void setLED(int pin)
    {
        const auto c = _color[getPinColorIndex(pin)];
        _led[c.index] = c.led[0];
        _led[c.index + 1] = c.led[1];
    }

    void setLED(int pin, int iR, int iG, int iB)
    {
        const auto c = _color[getPinColorIndex(pin)];
        _led[c.index].r=iR;
        _led[c.index].g=iG;
        _led[c.index].b=iB;
        _led[c.index + 1].r=iR;
        _led[c.index + 1].g=iG;
        _led[c.index + 1].b=iB;
    }

    void setAllLEDs(void)
    {
        for(const auto pin: switchPins)
        {
            setLED(pin);
        }
    }

    void setALL(int iR, int iG, int iB)
    {
      // set all leds in the array to the RGB color passed to this function
      for(auto i = 0; i < LED_COUNT; i++)
      {
          _led[i].r = iR;
          _led[i].g = iG;
          _led[i].b = iB;
      }

      // update the leds with new/current colors in the array
      updateALL();
    }

    void setColor(int pin, int iR, int iG, int iB)
    {
        const auto i = getPinColorIndex(pin);
        _color[i].led[0].r = iR;
        _color[i].led[0].g = iG;
        _color[i].led[0].b = iB;
        _color[i].led[1].r = iR;
        _color[i].led[1].g = iG;
        _color[i].led[1].b = iB;
    }

    void saveAllColors(void)
    {
        EEPROM.put(0, _color);
    }

    void setPinLEDMapping(uint8_t pin, uint8_t index)
    {
        _color[getPinColorIndex(pin)].index = index;
    }

    void resetAllLEDs()
    {
        for(auto i = 0; i < SWITCH_COUNT; i++)
        {
          const auto pin = switchPins[i];
          setColor(pin, WHITE);
          _color[getPinColorIndex(pin)].index = i * 2;
        }
        setAllLEDs();
    }

    void updateALL(void)
    {
      // update the leds with new/current colors and delay a little to avoid flickering (yea, it happens really, really fast!)
      // specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
      // port F0 drives LED data out
      //
      //  WS2811 timing based upon the threepixeldemo example by Alan Burlison ( alan@bleaklow.com )
      //    http://sourceforge.net/p/abavr/lib/ci/21a95bf1f6c437cac414e8efb0c80558e5c369db/tree/WS2811/
      //

      asm volatile( \
      /* initialise */ \
      "    cp %A[len], r1      ; check len > 0, return immediately if it is\n" \
      "    cpc %B[len], r1\n" \
      "    brne 1f\n" \
      "    rjmp 16f\n" \
      "1:  ld r18, Z+           ; load in first red byte to be output\n" \
      "    ld r19, Z+           ; load in first green byte to be output\n" \
      "    ld r20, Z+           ; load in first blue byte to be output\n" \
      "    ldi r27, 8           ; load inner loop counter\n" \
      "    in r26, __SREG__     ; timing-critical, so no interrupts\n" \
      "    cli\n" \
      /* green - loop over 8 bits */ \
      "2:  sbi  %[port], %[pin] ; pin lo -> hi\n" \
      "    sbrc r19, 7          ; test hi bit clear\n" \
      "    rjmp 3f              ; true, skip pin hi -> lo\n" \
      "    cbi  %[port], %[pin] ; false, pin hi -> lo\n" \
      "3:  sbrc r19, 7          ; equalise delay of both code paths\n" \
      "    rjmp 4f\n" \
      "4:  nop                  ; pulse timing delay\n" \
      "    nop\n" \
      "    nop\n" \
      "    nop\n" \
      "    nop\n" \
      "    nop\n" \
      "    lsl r19              ; shift to next bit\n" \
      "    dec r27              ; decrement loop counter\n" \
      "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
      "    brne 2b\n            ; loop if required\n" \
      "    ldi r27, 7           ; reload inner loop counter\n" \
      /* red - loop over first 7 bits */ \
      "5:  sbi %[port], %[pin]  ; pin lo -> hi\n" \
      "    sbrc r18, 7          ; test hi bit clear\n" \
      "    rjmp 6f              ; true, skip pin hi -> lo\n" \
      "    cbi %[port], %[pin]  ; false, pin hi -> lo\n" \
      "6:  sbrc r18, 7          ; equalise delay of both code paths\n" \
      "    rjmp 7f\n" \
      "7:  nop                  ; pulse timing delay\n" \
      "    nop\n" \
      "    nop\n" \
      "    nop\n" \
      "    nop\n" \
      "    nop\n" \
      "    lsl r18              ; shift to next bit\n" \
      "    dec r27              ; decrement inner loop counter\n" \
      "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
      "    brne 5b              ; inner loop, if required\n" \
      "    nop                  ; equalise delay of both code paths\n" \
      /* red, 8th bit - output & fetch next values */ \
      "    sbi %[port], %[pin]  ; pin lo -> hi\n" \
      "    sbrc r18, 7          ; test hi bit clear\n" \
      "    rjmp 8f              ; true, skip pin hi -> lo\n" \
      "    cbi %[port], %[pin]  ; false, pin hi -> lo\n" \
      "8:  sbrc r18, 7          ; equalise delay of both code paths\n" \
      "    rjmp 9f\n" \
      "9:  nop                  ; pulse timing delay\n" \
      "    nop\n" \
      "    nop\n" \
      "    ld r18, Z+           ; load next red byte\n" \
      "    ld r19, Z+           ; load next green byte\n" \
      "    ldi r27, 7           ; reload inner loop counter\n" \
      "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
      "    nop                  ; pulse timing delay\n" \
      "    nop\n" \
      /* blue - loop over first 7 bits */ \
      "10:  sbi %[port], %[pin] ; pin lo -> hi\n" \
      "    sbrc r20, 7          ; test hi bit clear\n" \
      "    rjmp 11f             ; true, skip pin hi -> lo\n" \
      "    cbi %[port], %[pin]  ; false, pin hi -> lo\n" \
      "11: sbrc r20, 7          ; equalise delay of both code paths\n" \
      "    rjmp 12f\n" \
      "12: nop                  ; pulse timing delay\n" \
      "    nop\n" \
      "    nop\n" \
      "    nop\n" \
      "    nop\n" \
      "    nop\n" \
      "    lsl r20              ; shift to next bit\n" \
      "    dec r27              ; decrement inner loop counter\n" \
      "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
      "    brne 10b             ; inner loop, if required\n" \
      "    nop                  ; equalise delay of both code paths\n" \
      /* blue, 8th bit -  output & handle outer loop */ \
      "    sbi %[port], %[pin]  ; pin lo -> hi\n" \
      "    sbrc r20, 7          ; test hi bit clear\n" \
      "    rjmp 13f             ; true, skip pin hi -> lo\n" \
      "    cbi %[port], %[pin]  ; false, pin hi -> lo\n" \
      "13: sbrc r20, 7          ; equalise delay of both code paths\n" \
      "    rjmp 14f\n" \
      "14: nop                  ; pulse timing delay\n" \
      "    nop\n" \
      "    ldi r27, 8           ; reload inner loop counter\n" \
      "    sbiw %A[len], 1      ; decrement outer loop counter\n" \
      "    breq 15f             ; exit outer loop if zero\n" \
      "    ld r20, Z+           ; load in next blue byte\n" \
      "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
      "    rjmp 2b              ; outer loop, if required\n" \
      "15: nop                  ; pulse timing delay\n" \
      "    cbi %[port], %[pin]  ; pin hi -> lo\n" \
      "    nop                  ; pulse timing delay\n" \
      "    nop\n" \
      "    out __SREG__, r26    ; reenable interrupts\n" \
      "16:\n" \
      : \
      : [rgb] "z" (&_led), \
        [len] "w" (sizeof(_led)/sizeof(_led[0])), \
        [port] "I" (_SFR_IO_ADDR(PORTF)), \
        [pin] "I" (0) \
      : "r18", "r19", "r20", "r26", "r27", "cc", "memory" \
      );
    }

    void switchHistoryClear(void)
    {
      static int  i;

      // initialize Switch History with zeros
      for(i=0;i<SWITCH_HISTORY_MAX;++i)
        _switchHistory[i] = 0;
    }

    void switchHistorySet(uint16_t latestValue)
    {
      static int  i;

      // add new history entry on change
      if(_switchHistory[0] != latestValue)
      {
        // shift historical values down list
        for(i=(SWITCH_HISTORY_MAX-1);i>0;--i)
          _switchHistory[i] = _switchHistory[i-1];

        // insert latest value at top of list
        _switchHistory[0] = latestValue;
      }
    }

    boolean switchHistoryTest( uint16_t a0=ATTACK_FALSE, uint16_t a1=ATTACK_FALSE, uint16_t a2=ATTACK_FALSE,  uint16_t a3=ATTACK_FALSE,  uint16_t a4=ATTACK_FALSE,  uint16_t a5=ATTACK_FALSE,  uint16_t a6=ATTACK_FALSE,  uint16_t a7=ATTACK_FALSE, uint16_t a8=ATTACK_FALSE, uint16_t a9=ATTACK_FALSE, uint16_t a10=ATTACK_FALSE, uint16_t a11=ATTACK_FALSE, uint16_t a12=ATTACK_FALSE, uint16_t a13=ATTACK_FALSE, uint16_t a14=ATTACK_FALSE, uint16_t a15=ATTACK_FALSE )
    {
      static boolean result;

      result = true;

      // if no parameters are passed to function then all default values are used and will result in a match returning a true
      // this is a great way to test the functionality without added complexity

      if(a0 != ATTACK_FALSE)
        if(a0 != _switchHistory[0])
          result = false;
      if(a1 != ATTACK_FALSE)
        if(a1 != _switchHistory[1])
          result = false;
      if(a2 != ATTACK_FALSE)
        if(a2 != _switchHistory[2])
          result = false;
      if(a3 != ATTACK_FALSE)
        if(a3 != _switchHistory[3])
          result = false;
      if(a4 != ATTACK_FALSE)
        if(a4 != _switchHistory[4])
          result = false;
      if(a5 != ATTACK_FALSE)
        if(a5 != _switchHistory[5])
          result = false;
      if(a6 != ATTACK_FALSE)
        if(a6 != _switchHistory[6])
          result = false;
      if(a7 != ATTACK_FALSE)
        if(a7 != _switchHistory[7])
          result = false;

      if(a8 != ATTACK_FALSE)
        if(a8 != _switchHistory[8])
          result = false;
      if(a9 != ATTACK_FALSE)
        if(a9 != _switchHistory[9])
          result = false;
      if(a10 != ATTACK_FALSE)
        if(a10 != _switchHistory[10])
          result = false;
      if(a11 != ATTACK_FALSE)
        if(a11 != _switchHistory[11])
          result = false;
      if(a12 != ATTACK_FALSE)
        if(a12 != _switchHistory[12])
          result = false;
      if(a13 != ATTACK_FALSE)
        if(a13 != _switchHistory[13])
          result = false;
      if(a14 != ATTACK_FALSE)
        if(a14 != _switchHistory[14])
          result = false;
      if(a15 != ATTACK_FALSE)
        if(a15 != _switchHistory[15])
          result = false;

      // clear history when matched = TRUE
      if(result == true)
        switchHistoryClear();

      return(result);
    }
};
