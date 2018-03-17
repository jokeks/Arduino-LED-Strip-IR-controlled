//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#ifndef LEDState_h
#define LEDState_h

#include <Arduino.h>

struct LEDState
{
    byte mode;
    uint32_t color1;
    uint32_t color2;
    byte speed = 100;
    byte brightness = 100;
};

#endif
