//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#ifndef ColorWipe_h
#define ColorWipe_h

#include "Arduino.h"
#include "BControl.h"
#include "../LEDState.h"
#include <Adafruit_NeoPixel.h>

/**
 * @brief  Wipe an old color with a new one.
 * Replace Color1 and call reset()
 * 
 */
class ColorWipe : public BControl
{
public:
  ColorWipe(Adafruit_NeoPixel *pStrip, LEDState *pState) : BControl(pStrip, pState){};
  void doStep();
  void reset();

private:
  int i;
};

#endif