//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#include "Arduino.h"
#include "LEDControl.h"
#include "controls/ColorWipe.h"
#include "controls/RainbowCycle.h"
#include "controls/RainbowChase.h"
#include "controls/ColorFadeCycle.h"
#include "../Memory.h"

LEDControl::LEDControl(Adafruit_NeoPixel *pStrip)
{
  this->_modes = new BControl *[MAX_MODES];
  this->_modes[0] = new ColorWipe(pStrip, &state);
  this->_modes[1] = new RainbowCycle(pStrip, &state);
  this->_modes[2] = new RainbowChase(pStrip, &state);
  this->_modes[3] = new ColorFadeCycle(pStrip, &state);
  this->_pStrip = pStrip;
}

LEDControl::~LEDControl()
{
  delete this->_modes;
}

/**
 * @brief Cycles all operation modes.
 * 
 */
void LEDControl::next()
{
  if (this->isOnline)
  {
    this->currentMode()->reset();
    this->state.mode = (this->state.mode + 1) % MAX_MODES;
  }
}

/**
 * @brief Sets the current operation mode. 
 * 
 * @param mode 
 */
void LEDControl::setMode(byte mode)
{
  if (this->isOnline)
  {
    this->currentMode()->reset();
    this->state.mode = mode % MAX_MODES;
  }
}

/**
 * @brief Call this every loop cycle to update the led strip accordingly.
 * 
 */
void LEDControl::loop()
{
  if (millis() - this->_lastStep >= this->state.speed)
  {
    this->_lastStep = millis();
    this->currentMode()->doStep();

    if (this->isOnline)
    {
      if(millis() - this->_lastSaveTime > 60 * 1000){
        this->_lastSaveTime = millis();
        Memory::saveState(this->state);
      }
    }
  }
}
/**
 * @brief Sets a new first color. Saves the old one as second color.
 * 
 * @param color Adafruit_NeoPixel::Color
 */
void LEDControl::setColor(uint32_t color)
{
  if (this->isOnline)
  {
    this->currentMode()->reset();
    this->state.color2 = this->state.color1;
    this->state.color1 = color;
  }
}
/**
 * @brief Turns the LED strip on and loads the last state from the memory.
 * 
 */
void LEDControl::on()
{
  //reset the save timer !
  this->_lastSaveTime = millis();

  //go online
  this->isOnline = true;
  Memory::loadState(this->state);
  this->currentMode()->reset();
  this->_pStrip->setBrightness(state.brightness);
}

/**
 * @brief This functun turns the LED strip offline and saves currend mode and color settings. 
 *        Afterwards the pixels are switched off.
 * 
 */
void LEDControl::off()
{
  Memory::saveState(this->state);
  this->setMode(0);
  this->setColor(Adafruit_NeoPixel::Color(0, 0, 0));
  this->setBrightness(0);
  this->isOnline = false;
}

/**
 * @brief Returns the current operation mode instance. 
 * 
 * @return BControl* Current mode instance pointer.
 */
BControl *LEDControl::currentMode()
{
  return this->_modes[this->state.mode];
}

void LEDControl::setSpeed(byte value)
{
  if (this->isOnline)
  {
    this->state.speed = value;
  }
}

/**
 * @brief Returns the current cycle time. 
 * 
 * @return byte Time to next cycle.
 */
byte LEDControl::getSpeed()
{
  return this->state.speed;
}

/**
 * @brief Sets the brightness of the strip.
 * 
 * @param value desired brightness.
 */
void LEDControl::setBrightness(byte value)
{
  if (this->isOnline)
  {
    this->state.brightness = value;
    this->_pStrip->setBrightness(value);
    this->_pStrip->show();
  }
}

/**
 * @brief Returns the current brightness.
 * 
 * @return byte Current brightness.
 */
byte LEDControl::getBrightness()
{
  return this->state.brightness;
}