//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#ifndef LEDUtil_h
#define LEDUtil_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

namespace LEDUtil {
  uint32_t Wheel(byte WheelPos);
  void DecodeColor(uint32_t color, byte (&result)[3]);
}

#endif
