//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#ifndef ColorFadeCycle_h
#define ColorFadeCycle_h

#include <Arduino.h>
#include "BControl.h"
#include <Adafruit_NeoPixel.h>

/**
 * @brief  Cycles two colors based on sinus transition.
 * 
 */
class ColorFadeCycle : public BControl
{
public:
  ColorFadeCycle(Adafruit_NeoPixel *pStrip, LEDState *pState);
  void doStep();
  void reset() {};

private:
  byte _chunks;
  uint16_t _position = 0;
  float _radPerPixel;

  uint32_t _twoColorWheel(float rad, byte (&color1)[3], byte (&color2)[3]);
};

#endif
