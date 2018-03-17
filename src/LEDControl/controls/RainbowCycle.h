//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#ifndef RainbowCycle_h
#define RainbowCycle_h

#include "Arduino.h"
#include "BControl.h"
#include <Adafruit_NeoPixel.h>

/**
 * @brief Rotates a rainbow with all colors around the strip.
 * 
 */
class RainbowCycle : public BControl
{
public:
  RainbowCycle(Adafruit_NeoPixel *pStrip, LEDState *pState) : BControl(pStrip, pState){};
  void doStep();
  void reset();

private:
  uint16_t i = 0;
};

#endif
