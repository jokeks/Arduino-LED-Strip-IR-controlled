//
// Copyright (c) Johannes Wiese. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef Memory_h
#define Memory_h

#include "Arduino.h"
#include <EEPROM.h>
#include "LEDControl/LEDState.h"


/**
 * @brief Manages the memory layout
 * 
 */
class Memory
{
public:
  static void saveState(LEDState &state);
  static void loadState(LEDState &state);

private:
  enum MemoryLayout
  {
    MEMORY_COLOR1_R,
    MEMORY_COLOR1_G,
    MEMORY_COLOR1_B,
    MEMORY_COLOR2_R,
    MEMORY_COLOR2_G,
    MEMORY_COLOR2_B,
    MEMORY_MODE,
    MEMORY_BRIGHTNESS,
    MEMORY_SPEED
  };

  static void write(MemoryLayout position, byte value);
  static byte read(MemoryLayout position);
  static void setColor1(uint32_t color);
  static void setColor2(uint32_t color);
};

#endif