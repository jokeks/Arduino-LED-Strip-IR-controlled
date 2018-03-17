//
// Copyright (c) Johannes Wiese. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include <Arduino.h>
#include "ColorCycle.h"

void ColorCycle::doStep()
{
    int chunkSize = this->_pStrip->numPixels() / this->_chunks;

    for (byte i = 0; i < this->_chunks; i++)
    {
        uint16_t position = ((i * chunkSize) + this->_position) % this->_pStrip->numPixels();
        if (i % 2 == 0)
        {
            this->_pStrip->setPixelColor(position, this->pState->color1);
        }
        else
        {
            this->_pStrip->setPixelColor(position, this->pState->color2);
        }
    }
    this->_pStrip->show();
    this->_position = this->_position + 1 % chunkSize;
}
