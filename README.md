# Wireless Switch

A simple DIY wireless switch

## Usage

Current usage is a bit funky. Eventually, it should be streamlined.

- From your wireless device, connect to "ESP8266 Thing XXXX"
- The password is "sparkfun"
- Open a browser on http://192.168.41.1

The LED On and LED Off buttons are reversed.

The Read Analog does nothing.

## Hardware

TODO

## Deployment

### Generic ESP8266 board

Follow these steps to deploy to Olimex ESP8266-dev.

First put the ESP8266 in programming mode. This is usually via some buttons on the ESP8266 integration board.

In Ardnuio IDE:

- tools sketch esp8266 sketch data upload
- sketch upload

IMPORTANT! the data upload has to be done before the sketch upload

Remember that the FTDI supplies barely enough current to run WiFi.

## Testing

There are no unit tests, although it would be nice to do some simple ones for an arduino project.
There's also some Javascript logic that could be unit tested.

To aid in integration testing, there's a node server which simulates the ESP Web Server. It serves static
file directly from the data folder and provides a fake API. This is handy for testing and debugging the front end
code.

## Development

Use the Arduino IDE

Recommend using IDE: Prefernces > use External Editor

## Arduino IDE

Library Manager

Add ArduinoJson

## Links and references

https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/examples/FSBrowser/FSBrowser.ino

