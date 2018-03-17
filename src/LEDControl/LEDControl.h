//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#ifndef LEDControl_h
#define LEDControl_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "LEDState.h"
#include "controls/BControl.h"
#include "controls/ColorWipe.h"

class LEDControl
{
public:
  bool isOnline = false;
  
  LEDControl(Adafruit_NeoPixel *strip);
  ~LEDControl();
  void next();
  void loop();
  void setMode(byte mode);
  void setColor(uint32_t color);
  void off();
  void on();
  BControl *currentMode();
  void setSpeed(byte value);
  byte getSpeed();
  void setBrightness(byte value);
  byte getBrightness();

private:
  static const byte MAX_MODES = 4;
  unsigned long _lastStep = millis();
  unsigned long _lastSaveTime = millis();
  LEDState state;
  Adafruit_NeoPixel *_pStrip;
  BControl **_modes;
};

#endif
