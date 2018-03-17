//
// Copyright (c) Johannes Wiese. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include <Adafruit_NeoPixel.h>
#include <IRLremote.h>

#include "src/LEDControl/LEDControl.h"
#include "src/Memory.h"
#include "src/RemoteAction.h"

#define DEBUG false
#define BYTE_MAX 255

//Pin configuration
#define RECV_PIN 2   //IR Reciver
#define BUTTON_PIN 3 //Button: manually switch modes
#define PIXEL_PIN 9  //LED strip data

//LED Configuration
#define PIXEL_COUNT 100
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_BRG + NEO_KHZ800);

//Wrap the strip with our own manager
LEDControl manager = LEDControl(&strip);

//Instantiate a NEC encoding receiver.
//All cheap controller primarily use nec encoding.
CNec IRLremote;

//Sets the controller->function mapping
//To create own mappings take a look at the end of the file.
#define REMOTE 1

//Store the last qualified command.
//If the button is pressed down, the comand "button is hold down"
//for all buttons will be 0xFF.
Nec_command_t lastCommand = 0;

void setup()
{
#if DEBUG
  //Init serial for potential debugging
  Serial.begin(115200);
  while (!Serial)
  {
    ;
  }
  Serial.println("Starting Setup");
#endif
  //Configure manual mode button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  //Init ir
  if (!IRLremote.begin(RECV_PIN))
  {
#if DEBUG
    Serial.println(F("You did not choose a valid pin."));
#endif
  }

  //Init led strip
  strip.begin();
  strip.setBrightness(0);
  strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
  //Check for new IR input
  if (IRLremote.available())
  {
    queryIRData(IRLremote.read());
  }

  //process the button pin
  queryButton();

  //Do stuff that disables interrupts
  if (!IRLremote.receiving())
  {
    manager.loop();

#if DEBUG
    Serial.println(freeMemory());
#endif
  }
}

/**
 * @brief Checks for a repeating command and decodes the comman. 
 * 
 * @param data current ir data
 */
void queryIRData(Nec_data_t data)
{
  if (data.command != 0)
  {
    lastCommand = data.command;
    decodeIRCommand(data.command, false);
  }
  else
  {
    decodeIRCommand(lastCommand, true);
  }
}

bool lastButtonState = HIGH;
/**
 * @brief Evaluate the manual mode button.
 * 
 */

void queryButton()
{
  if (digitalRead(BUTTON_PIN) != lastButtonState)
  {
    delay(20);
    if (digitalRead(BUTTON_PIN) != lastButtonState)
    {
      lastButtonState = !lastButtonState;
      if (lastButtonState == LOW)
      {
        manager.next();
      }
    }
  }
}

/**
 * @brief Maps the controller command via the controllermapping
 *  and executes the desired function. 
 * 
 * @command IR-Code
 * @repeat is 
 */
void decodeIRCommand(Nec_command_t command, boolean isRepeat)
{
#if DEBUG
  Serial.print("Execute Command: ");
  Serial.println(command, HEX);
#endif
  switch (mapRemote(command))
  {
  //ON/OFF
  case ON_OFF:
    if (isRepeat)
      break;
    if (manager.isOnline)
    {
      manager.off();
    }
    else
    {
      manager.on();
    }
    break;

  case C_RED_255_0_0:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(255, 0, 0));
    break;

  case C_ORANGE_255_60_0:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(255, 60, 0));
    break;

  case C_ORANGE_255_120_0:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(255, 120, 0));
    break;
  case C_ORANGE_255_180_0:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(255, 180, 0));
    break;

  case C_YELLOW_255_255_0:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(255, 255, 0));
    break;

  case C_GREEN_0_255_0_50:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(0, 255, 0));
    break;

  case C_LIGHTGREEN_50_255_50:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(50, 255, 50));
    break;

  case C_LIGHTBLUE_1:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(102, 255, 255));
    break;
  case C_LIGHTBLUE_2:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(0, 153, 255));
    break;

  case C_LIGHTBLUE_3:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(0, 102, 255));
    break;

  case C_BLUE_0_0_255:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(0, 0, 255));
    break;

  case C_DARKBLUE_102_102_255:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(102, 102, 255));
    break;

  case C_PURPLE_153_102_255:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(153, 102, 255));
    break;

  case C_LIGHTPURPLE_204_51_255:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(204, 51, 255));
    break;

  case C_PINK_255_0_255:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(255, 0, 255));
    break;

  case C_WHITE_255_255_255:
    if (isRepeat)
      break;
    manager.setColor(strip.Color(255, 255, 255));
    break;

  case MODE_1:
    manager.setMode(0);
    break;

  case MODE_2:
    manager.setMode(1);
    break;

  case MODE_3:
    manager.setMode(2);
    break;

  case MODE_4:
    manager.setMode(3);
    break;

  case BRIGHTNESS_UP:
    if (manager.getBrightness() > BYTE_MAX - 10)
    {
      manager.setBrightness(255);
    }
    else
    {
      manager.setBrightness(manager.getBrightness() + 5);
    }
    break;

  case BRIGHTNESS_DOWN:
    if (manager.getBrightness() > 15)
    {
      manager.setBrightness(manager.getBrightness() - 5);
    }
    else
    {
      manager.setBrightness(10);
    }
    break;

  case SPEED_CYCLE:
    //overflow allowed
    manager.setSpeed(manager.getSpeed() + 10);
    break;

  case SPEED_UP:
    if (manager.getSpeed() < 10)
    {
      manager.setSpeed(1);
    }
    else
    {
      manager.setSpeed(manager.getSpeed() - 5);
    }
    break;

  default:
    break;
  }
}

#if REMOTE == 0
/**
 * @brief Maps a nec command of the remote to a RemoteAction.
 * A 3x7 key remote with a mp3 tag on it.
 * 
 * @param command Current command
 * @return RemoteAction Desired action
 */
RemoteAction mapRemote(Nec_command_t command)
{
  switch (command)
  {
    //ON/OFF
  case 0x45:
    return ON;
  //1
  case 0x0C:
    return MODE_1;
  //2
  case 0x18:
    return MODE_2;
  //3
  case 0x5E:
    return MODE_3;
  //4
  case 0x08:
    return MODE_4;
  //5
  case 0x1C:

    break;
  //6
  case 0x5A:
    break;
  //7
  case 0x42:
    break;
  //8
  case 0x52:
    break;
  //9
  case 0x4A:
    break;
  //0
  case 0x16:
    break;
  //-
  case 0x15:
    return BRIGHTNESS_DOWN;
    break;
  //+
  case 0x09:
    return BRIGHTNESS_UP;
    break;
  //Mode
  case 0x46:
    break;
  //Mute
  case 0x47:
    break;
  //Start/Stopp
  case 0x44:
    break;
  //Backward
  case 0x40:
    break;
  //Forward
  case 0x43:
    break;
  //EQ
  case 0x07:
    break;
  //Switch
  case 0x19:
    break;
  //U/SD
  case 0x0D:
    break;
  case 0XFF:
    break;
  default:
    break;
  }
  return NOOP;
}

#elif REMOTE == 1
/**
 * @brief Maps a nec command of the remote to a RemoteAction.
 * 4x6Key color remote ak the small led remote, 
 * wich is shipped with the most controllers.
 * 
 * @param command Current command
 * @return RemoteAction Desired action
 */
RemoteAction mapRemote(Nec_command_t command)
{
  switch (command)
  {
  //OFF
  case 0x6:
    return SPEED_CYCLE;
  case 0x7:
    return ON_OFF;
  case 0x5:
    return BRIGHTNESS_UP;
  case 0x4:
    return BRIGHTNESS_DOWN;
  case 0x9:
    return C_RED_255_0_0;
  case 0xD:
    return C_ORANGE_255_60_0;
  case 0x15:
    return C_ORANGE_255_120_0;
  case 0x19:
    return C_ORANGE_255_180_0;
  case 0x11:
    return C_YELLOW_255_255_0;
  case 0x8:
    return C_GREEN_0_255_0_50;
  case 0xC:
    return C_LIGHTGREEN_50_255_50;
  case 0x14:
    return C_LIGHTBLUE_1;
  case 0x18:
    return C_LIGHTBLUE_2;
  case 0x10:
    return C_LIGHTBLUE_3;
  case 0xA:
    return C_BLUE_0_0_255;
  case 0xE:
    return C_DARKBLUE_102_102_255;
  case 0x16:
    return C_PURPLE_153_102_255;
  case 0x1A:
    return C_LIGHTPURPLE_204_51_255;
  case 0x12:
    return C_PINK_255_0_255;
  case 0xB:
    return C_WHITE_255_255_255;
  case 0xF:
    return MODE_1;
  case 0x17:
    return MODE_2;
  case 0x1B:
    return MODE_3;
  case 0x13:
    return MODE_4;
  default:
    return NOOP;
  }
}
#endif

#if DEBUG

  //Source(MIT): https://github.com/mpflaga/Arduino-MemoryFree/blob/master/MemoryFree.cpp

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char *sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif // __arm__

int freeMemory()
{
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char *>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif // __arm__
}

#endif