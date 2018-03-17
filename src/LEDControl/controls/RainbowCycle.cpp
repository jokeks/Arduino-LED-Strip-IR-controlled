//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#include "Arduino.h"
#include "RainbowCycle.h"
#include "../LEDUtil.h"

using namespace LEDUtil;

void RainbowCycle::doStep()
{
    if (this->i >= 256 * 5)
    {
        this->i = 0;
    }

    uint16_t j;
    for (j = 0; j < this->_pStrip->numPixels(); j++)
    {
        this->_pStrip->setPixelColor(j, Wheel(((j * 256 / this->_pStrip->numPixels()) + this->i) & 255));
    }

    this->_pStrip->show();
    this->i++;
}

void RainbowCycle::reset()
{
    this->i = random(256 * 5);
}