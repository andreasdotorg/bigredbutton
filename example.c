/* Big Red Button USB HID
 * https://github.com/andreas23/bigredbutton
 * Copyright (c) 2015 Andreas Bogk
 *
 * Based on:
 * 
 * Keyboard example for Teensy USB Development Board
 * http://www.pjrc.com/teensy/usb_keyboard.html
 * Copyright (c) 2008 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_keyboard.h"

#define LED_CONFIG       (DDRD |= (1<<6))
#define LED_ON           (PORTD &= ~(1<<6))
#define LED_OFF          (PORTD |= (1<<6))
#define CPU_PRESCALE(n)  (CLKPR = 0x80, CLKPR = (n))

int main(void)
{
  uint8_t b, mask;
  uint8_t b_prev=0xFF;

  // set for 16 MHz clock
  CPU_PRESCALE(0);

  DDRB = 0x00;
  PORTB = 0xFF;

  usb_init();
  while (!usb_configured());
  _delay_ms(1000);

  while (1) {
    b = PINB;
    mask = 1;
    if (((b & mask) == 0) && (b_prev & mask) != 0) {
      usb_keyboard_press(KEY_F5, 0);
    }
    b_prev = b;
    _delay_ms(10);
  }
}
