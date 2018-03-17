//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#ifndef RainbowChase_h
#define RainbowChase_h

#include "Arduino.h"
#include "BControl.h"
#include <Adafruit_NeoPixel.h>

/**
 * @brief Rotates colors around the strip and crates a moving effect with black pixels.
 * 
 */
class RainbowChase : public BControl
{
public:
  RainbowChase(Adafruit_NeoPixel *pStrip, LEDState *pState) : BControl(pStrip, pState){};
  void doStep();
  void reset();

private:
  short q = 0;
  byte wheelpos = 0;
};

#endif
