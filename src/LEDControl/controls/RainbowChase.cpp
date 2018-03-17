//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#include "Arduino.h"
#include "RainbowChase.h"
#include "../LEDUtil.h"

using namespace LEDUtil;

void RainbowChase::doStep()
{
    for (int i = 0; i < this->_pStrip->numPixels(); i = i + 3)
    {
        //turn of every pixel from the previous loop
        this->_pStrip->setPixelColor(i + ((this->q - 1) % 3), 0);
        this->_pStrip->setPixelColor(i + this->q, Wheel((i + this->wheelpos) % 256)); //turn every third pixel on
    }

    this->_pStrip->show();
    this->q = (this->q + 1) % 3;
    this->wheelpos = (this->wheelpos + 1) % 256;
}

/**
 * @brief Reset the state manager to the first state
 * 
 */
void RainbowChase::reset()
{
    this->q = 0;
    this->wheelpos = (byte)random(255);
}