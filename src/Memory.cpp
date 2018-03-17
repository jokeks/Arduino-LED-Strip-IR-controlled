//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#include "Memory.h"
#include <Adafruit_NeoPixel.h>
#include "LEDControl/LEDUtil.h"

/**
 * @brief Wrapper for the EEPROM write function
 * 
 * @param position Memory position
 * @param value value
 */
void Memory::write(MemoryLayout position, byte value)
{
    EEPROM.update(position, value);
}

/**
 * @brief  Wrapper for the EEPROM read function
 * 
 * @param position Memory position
 * @return byte 
 */
byte Memory::read(MemoryLayout position)
{
    return EEPROM.read(position);
}

/**
 * @brief Splits the color and saves the values at position 2
 * 
 * @param color Color to save
 */
void Memory::setColor1(uint32_t color)
{
    byte rgb[3];
    LEDUtil::DecodeColor(color, rgb);
    Memory::write(MEMORY_COLOR1_R, rgb[0]);
    Memory::write(MEMORY_COLOR1_G, rgb[1]);
    Memory::write(MEMORY_COLOR1_B, rgb[2]);
}

/**
 * @brief Splits the color and saves the values at position 1
 * 
 * @param color Color to save
 */
void Memory::setColor2(uint32_t color)
{
    byte rgb[3];
    LEDUtil::DecodeColor(color, rgb);
    Memory::write(MEMORY_COLOR2_R, rgb[0]);
    Memory::write(MEMORY_COLOR2_G, rgb[1]);
    Memory::write(MEMORY_COLOR2_B, rgb[2]);
}

/**
 * @brief Saves the values of a given state to the EEPROM
 * 
 * @param state LEDState to save
 */
void Memory::saveState(LEDState &state)
{
    Memory::setColor1(state.color1);
    Memory::setColor2(state.color2);
    Memory::write(MEMORY_MODE, state.mode);
    Memory::write(MEMORY_SPEED, state.speed);
    Memory::write(MEMORY_BRIGHTNESS, state.brightness);
}

/**
 * @brief Reads the state from the EEPROM
 * 
 * @param outState Reference to a LEDState object
 */
void Memory::loadState(LEDState &outState)
{
    outState.color1 = Adafruit_NeoPixel::Color(
        Memory::read(MEMORY_COLOR1_R),
        Memory::read(MEMORY_COLOR1_G),
        Memory::read(MEMORY_COLOR1_B));
    outState.color2 = Adafruit_NeoPixel::Color(
        Memory::read(MEMORY_COLOR2_R),
        Memory::read(MEMORY_COLOR2_G),
        Memory::read(MEMORY_COLOR2_B));
    outState.brightness = Memory::read(MEMORY_BRIGHTNESS);
    outState.speed = Memory::read(MEMORY_SPEED);
    outState.mode = Memory::read(MEMORY_MODE);
}
