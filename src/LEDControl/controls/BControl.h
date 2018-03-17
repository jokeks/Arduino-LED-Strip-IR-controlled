//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#ifndef BControl_h
#define BControl_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "../LEDState.h"

/**
 * @brief Base class for all state machines 
 * 
 */
class BControl
{
public:
  BControl(Adafruit_NeoPixel *strip, LEDState *state);
  virtual void doStep() = 0;
  virtual void reset() {};

protected:
  Adafruit_NeoPixel *_pStrip;
  LEDState *pState;
};

#endif
