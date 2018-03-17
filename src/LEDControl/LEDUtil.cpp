//
// Copyright (c) Johannes Wiese. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "Arduino.h"
#include "LEDUtil.h"
#include <Adafruit_NeoPixel.h>

namespace LEDUtil
{

  /**
   * @brief Circles the RGB spectrum
   * 
   * @param WheelPos Wheel position 0-255
   * @param pStrip Adafruit_NeoPixel strip
   * @return uint32_t Adafruit_NeoPixel color
   */
  uint32_t Wheel(byte WheelPos)
  {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
      return Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
      WheelPos -= 85;
      return Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }

  /**
   * @brief Decodes a color into RGB bytes
   * 
   * @param color Adafruit_NeoPixel color
   * @param result 3 byte array RED GREEN BLUE
   */
  void DecodeColor(uint32_t color, byte (&result)[3])
  {
    result[0] = static_cast<byte>((color & 0x00FF0000) >> 16);
    result[1] = static_cast<byte>((color & 0x0000FF00) >> 8),
    result[2] = static_cast<byte>(color & 0x000000FF);
  }
}