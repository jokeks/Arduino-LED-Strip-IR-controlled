Arduino WS2811 / WS2812B with IR-Remote
==================

This program combines the Neopixel library from Adafruit and the IRLremote library to create a remote controllable LED strip. Anyone who is interested in development should take a look at [FastLED](http://fastled.io/), which provides many more functions to manipulate the colors. I found FastLed after i was nearly done with this project. 

For further development, take a look at a VS Code, which supports the development of Arduino projects including sketch uploading and serial monitor.

 ** This is my C++ learning project, so improvements are welcome. **

# Dependencies 

* [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel): LED Strip library
* [IRLremote](https://github.com/NicoHood/IRLremote): Infrared library

# Installation 

Install the dependencies with the Arduino IDE and open the ** led.ino **. Now configure the values and then upload the sketch to your Arduino.

# Configuration

Depending on the strip you are using, configure the transmission configuration and the stripe length(PIXEL_COUNT). [More Info](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use)
```
#define PIXEL_COUNT 100
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_BRG + NEO_KHZ800);
```
Configure the pin layout. Keep in mind, that the IR receiver only works  with interrupt enabled pins .

```
#define RECV_PIN 2 //IR Reciver
#define BUTTON_PIN 3 //Button: manually switch modes
#define PIXEL_PIN 9 //LED strip data 
```

# Arduino Nano configuration example
A quick schema of my used hardware. The pin-configuration of the led.ino matches this picture.

[schema]:  "Arduino Nano sample configuration"


# Thanks
* [Arduino-MemoryFree](https://github.com/mpflaga/Arduino-MemoryFree): the free memory function
