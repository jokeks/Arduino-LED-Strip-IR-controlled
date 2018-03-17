//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#include "Arduino.h"
#include "ColorWipe.h"

#define CHUNK_SIZE 10

void ColorWipe::doStep()
{
    if (this->i < CHUNK_SIZE)
    {
        byte n = this->_pStrip->numPixels() / CHUNK_SIZE;

        for (int k = 0; k < n + 1; k++)
        {
            int pixel = (k * CHUNK_SIZE) + i;
            if (pixel < this->_pStrip->numPixels())
            {
                this->_pStrip->setPixelColor(pixel, this->pState->color1);
            }
        }
        this->_pStrip->show();
        this->i++;
    }
}

void ColorWipe::reset()
{
    this->i = 0;
}