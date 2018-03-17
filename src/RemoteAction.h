//  
// Copyright (c) Johannes Wiese. All rights reserved.  
// See LICENSE file in the project root for full license information.  
//

#ifndef RemoteAction_h
#define RemoteAction_h

enum RemoteAction
{
  ON,
  OFF,
  ON_OFF,
  BRIGHTNESS_UP,
  BRIGHTNESS_DOWN,
  SPEED_UP,
  SPEED_DOWN,
  SPEED_CYCLE,
  C_RED_255_0_0,
  C_ORANGE_255_60_0,
  C_ORANGE_255_120_0,
  C_ORANGE_255_180_0,
  C_YELLOW_255_255_0,
  C_GREEN_0_255_0_50,
  C_LIGHTGREEN_50_255_50,
  C_LIGHTBLUE_1,
  C_LIGHTBLUE_2,
  C_LIGHTBLUE_3,
  C_BLUE_0_0_255,
  C_DARKBLUE_102_102_255,
  C_PURPLE_153_102_255,
  C_LIGHTPURPLE_204_51_255,
  C_PINK_255_0_255,
  C_WHITE_255_255_255,
  MODE_1,
  MODE_2,
  MODE_3,
  MODE_4,
  NOOP
};

#endif