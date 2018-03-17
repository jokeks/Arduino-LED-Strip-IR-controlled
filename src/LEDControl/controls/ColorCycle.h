//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#ifndef ColorCycle_h
#define ColorCycle_h

#include <Arduino.h>
#include "BControl.h"
#include <Adafruit_NeoPixel.h>

/**
 * @brief Cycles two colors with a hard transition. 
 * 
 */
class ColorCycle : public BControl
{
  public:
    ColorCycle(Adafruit_NeoPixel *pStrip, LEDState *pState) : BControl(pStrip, pState){
        this->_chunks = pStrip->numPixels() / 15;
    };
    void doStep();
    void reset();

    private:
     uint16_t _position = 0;
     byte _chunks;
};

#endif
