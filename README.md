# Kaimana Mini LED Driver Controller

This is a controller for [Kaimana Mini LED Driver](https://paradisearcadeshop.com/products/paradise-kaimana-mini-led-driver-pcb) and [Kaimana J2 RGB LED](https://paradisearcadeshop.com/products/paradise-kaimana-j2-rgb-led).

## Features

- Tourney mode
- LED color setting

### Tourney mode

Tourney mode is to off all LEDs.

#### How to enable/disable Tourney mode

Press and hold the `START` button at least 3 seconds, then Tourney mode is enabled/disabled and also all LEDs are turned on for about 3 seconds.

### LED color setting

You can set a light color of LED for each button.

#### How to set LED colors

To enter setting mode, press and hold the `SELECT` button at least 3 seconds when Tourney mode is disabled.
All LEDs are turned on if it is in selection mode of setting mode.
In that state, press a button you want to set a color of LED.

If you are selecting the button that is move buttons(`LEFT`, `RIGHT`, `DOWN` and `UP`), attack buttons become setting buttons.
If you are selecting the button that is attack buttons(`P` and `K` buttons), move buttons become setting buttons.

Selected button | `P` or `K` | `LEFT`, `RIGHT`, `DOWN` or `UP` | Behavior
---- | ---- | ---- | ----
　 | `LEFT` | `P1` or `K1` | Increase 15 Red color value
　 | `DOWN` | `P2` or `K2` | Increase 15 Green color value
　 | `RIGHT` | `P3` or `K3` | Increase 15 Blue color value
　 | `START` | `START` | Set color and return to selection mode
　 | `SELECT` | `SELECT` | Reset color

After finish to set all LED colors you want, return to selection mode, then press and hold the `SELECT` button at least 3 seconds to save LED colors you set.

## Copyright

Paradise Arcade Shop Kaimana LED Driver Board
Initial Release October 15, 2013


Copyright 2013 Paradise Arcade Shop, ParadiseArcadeShop.com
All rights reserved.  Use is subject to license terms.

Code is provided for entertainment purposes and use with the Kaimana controller.
Code may be copied, modified, resused with this Copyright notice.
No commercial use without written permission from Paradise Arcade Shop.

Paradise Arcade Shop Kaimana LED Driver Board
Initial Release October 15, 2013

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.



The Kaimana class library is based on original source released by ParadiseArcadeShop.com
with feedback from the community.

Created:  October 24, 2013    zonbipanda  -- Arduino 1.0.5 Support

Revised:  October 29, 2013    zonbipanda

Revised:  April   11, 2015    zonbipanda  -- Arduino 1.6.3 Support

_