//
// Copyright (c) Johannes Wiese. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include <Arduino.h>
#include "ColorFadeCycle.h"
#include "../LEDUtil.h"

#define CHUNK_SIZE 30

using namespace LEDUtil;

ColorFadeCycle::ColorFadeCycle(Adafruit_NeoPixel *pStrip, LEDState *pState) : BControl(pStrip, pState)
{
    //precalculate the chunks
    this->_chunks = pStrip->numPixels() / CHUNK_SIZE;
    this->_radPerPixel = (2 * PI * this->_chunks) / this->_pStrip->numPixels();
};


void ColorFadeCycle::doStep()
{
    //prepare the loop
    //decode the current colors
    byte color1[3], color2[3];
    DecodeColor(this->pState->color1, color1);
    DecodeColor(this->pState->color2, color2);

    //loop all pixels
    for (uint16_t i = 0; i < this->_pStrip->numPixels(); i++)
    {
        uint16_t pixel = (i + this->_position) % this->_pStrip->numPixels();
        uint32_t color = this->_twoColorWheel(i * this->_radPerPixel, color1, color2);
        this->_pStrip->setPixelColor(pixel, color);
    }

    this->_pStrip->show();
    this->_position = this->_position + 1 % this->_pStrip->numPixels();
}

/**
 * @brief Combines two colors based on sinus.
 * 
 * @param rad Position on the color wheel, which determines the color.
 * @return uint32_t Adafruit_NeoPixel::Color
 */
uint32_t ColorFadeCycle::_twoColorWheel(float rad, byte (&color1)[3], byte (&color2)[3])
{
    // a + b = 1!
    float a = (sin(rad) + 1) / 2;
    float b = 1 - a;

    return Adafruit_NeoPixel::Color(
        static_cast<byte>(color1[0] * a + color2[0] * b),
        static_cast<byte>(color1[1] * a + color2[1] * b),
        static_cast<byte>(color1[2] * a + color2[2] * b));
}