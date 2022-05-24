# RgbLedStripController

This project is an **alternative** to the **RF controller** that comes with **LED strips**, with this you can control the strip by **serial communication** using a command line program, also you can select an specific color in RGB format. 

Scheme and Components
---------------------

- 3x 10kΩ 1/4w Resistors
- 3x F530NS Power MOSFETs or similar with fast-switching, low-on-resistance, VDSS > ~15v and ID > strip consume + ~10%.
- 1x push button (Optional)
- 1x Arduino (Eg: Nano, Micro) or any programmable board with min 3 PWM output channels like ESP8266 or Raspberry PI Pico
- 1x USB connection to PC
- 1x 12v power supply like a charger or the pc power supply

<img src="https://i.ibb.co/4MG5VJx/rgb-led-strip-controller.png" height="600px">

Installation
------------

First you need to clone the repository or [download it](https://github.com/MarcosTypeAP/RgbLedStripController/archive/refs/heads/main.zip).

And copy the command line program to a folder in your $PATH environment variable so you can run it anywhere.

```bash
#!/bin/bash

git clone https://github.com/MarcosTypeAP/RgbLedStripController.git
cd RgbLedStripController/
cp config-rgb $HOME/.local/bin/
```

You also need to install [**Arduino IDE**](https://www.arduino.cc/en/software) and then install on Arduino IDE the board manager corresponding to your programmable board if it is not Arduino.

#### Config controller

You can adapt the sketch to your board and change the defautl strip color modifing the first lines of `rgbLedStripController.ino`:

```c
// Config section
///////////////////////////////////////////////////////////
const int LED_R = 11;          // Red LED Pin
const int LED_G = 10;          // Green LED Pin
const int LED_B = 9;           // Blue LED Pin
const int BUTTON = 3;          // Button Pin
const int DEFAULT_R = 255;     // Default Red value
const int DEFAULT_G = 70;      // Default Green value
const int DEFAULT_B = 15;      // Default Blue value
const int PWM_RESOLUTION = 8;  // PWM resolution in Bits
///////////////////////////////////////////////////////////
```

#### Upload to board

In case of Arduino Nano open the sketch on Arduino IDE and follow the next steps:
1. Tools->Board->Arduino AVR Boards->Arduino Nano
2. Tools->Processor->ATmega328P
3. Port->/dev/ttyUSB0 or can be 1,2,3...

The port can be checked running `ls /dev/ttyUSB*` before and after connection the board and see which one appears. If you have problems to upload the sketch, maybe you can fix it changing the processor to "ATmega328P (Old Bootloader)".

For uploading you just need to go to Sketch->Upload, then make all restant connections and it's done.

Usage
-----

#### Manual

If you added a button, you can control it manually:
- Press = Turn ON/OFF the strip (`#FF460F` by default)
- Hold = Activate/Deactivate the control by command line

#### Command line

To use it, run `config-rgb` with the following arguments:
- `--dec <R> <G> <B>` Change the strip color by decimal RGB format
- `--hex <R> <G> <B>` Change the strip color by hexadecimal RGB format 
- `-d` Deactivate the control by command line and turn OFF the strip
- `no argument` Turn OFF the strip

The values must be between 0 and the max PWM value, 8bit (0-255 / 0-FF) by default.

###### Examples

```bash
config-rgb --dec 255 70 15
config-rgb
config-rgb --hex FF 46 F
config-rgb -d
```
