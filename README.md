# esp8266-fan-control

ESP8266-based PWM fan control with a BME280 temperature sensor.

## Hardware

The following hardware is used:
* [Adafruit Feather HUZZAH with ESP8266](https://www.adafruit.com/products/2821)
* [Noctua NF-A12x25 5V PWM](https://noctua.at/en/nf-a12x25-5v-pwm)
* BME280 sensor
* 2kΩ resistor (anything above 1kΩ should work, do your own research if you don't want to risk frying your ESP8266) 

## Setup

The ESP8266 needs to be powered via USB.

![Diagram](esp8266-fan-control-diagram.png)

The BME280 sensor gets powered via the 3.3V and GND ports and data communication is connected via I2C using the SCL and SDA pins.

The PWM fan is powered (yellow wire) via the VBUS pin which provides 5V directly from the USB power. Connect GND of the fan (black wire) to the same GND as the sensor. For the PWM signal (blue wire) use GPIO12 (pin 6). The RPM speed signal (green wire) needs a 5V GPIO signal but the ESP8266's GPIO pins run on 3.3V. This can be solved by using a pull-up resistor (I use a 2kΩ resistor, larger resistors should work as well). Connect the RPM speed signal to GPIO13 (pin 7) and to the 3.3V pin through the pull-up resistor. For more details on the Noctua PWM fan specifications, check out the [Noctua PWM specifications white paper](https://noctua.at/pub/media/wysiwyg/Noctua_PWM_specifications_white_paper.pdf)

## Software

This software uses Adafruit's ESP8266 Feather board with the Arduino IDE as described [here](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide).

## Behavior
