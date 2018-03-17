//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#include "BControl.h"
#include <Arduino.h>

/**
 * @brief Construct a new BControl::BControl object
 * 
 * @param pStrip Pointer to the Adafruit_NeoPixel strip
 * @param pState Pointer to the LEDState object
 */
BControl::BControl(Adafruit_NeoPixel *pStrip, LEDState *pState)
{
    this->pState = pState;
    this->_pStrip = pStrip;
    this->reset();
}