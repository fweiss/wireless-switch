# Wireless Switch

A simple DIY wireless switch using ESP8266

Since starting this project late 2016, we've seen the very capable ITEAD Sonoff line of DIY remote WiFi modules.
The Sonoff Basic module is available for a mind-blowing $5! See links below.

## Usage

The ESP8266 can be accessed wia WiFi in two modes:

- Access Point (AP)
- Station (STA)

These modes can also be combined, but we'll skip this for the time being.

Currently, we're using station mode. Although it requires embedding the SSID and password in the code,
it makes debugging easier, because it connects on power up. In AP mode, we have to manually join the network
from a device.

Once the ESP8266 has successfully connected to our WiFi router, the router should remember the MAC address
and use the same DHCP IP address when the ESP8266 reconnects.

### UI

The UI displays a large switch. Clicking the switch toggles between OFF and ON.

![UI Screenshot](/doc/screen-shot.png)

- clicking or tapping switch UI changes the state
- page reload queries wireless switch for current state
- changing state does not reload page

## Hardware

We are currently using the OLIMEX ESP8266 WiFi Dev component. It's mounted on a small breadboard. The breadboard provides:

- terminals for 3.3 VDC supply
- terminals to control 10 mA solid state relay LED
- terminal for 3.3 V FTDI programming
- switch to control programming mode

There's [more detialed information on the hardware.](HARDWARE.md)

## Deployment

Deploy the code via the Arduino IDE toolchain. Deployment was done with version 1.6.8.

### Olimex MOD-WIFI-ESP8266-DEV board

Follow these steps to deploy to MOD-WIFI-ESP8266-DEV board.

#### Setup for deployment

1. In the Arduino IDE, choose Tools > Board, and select 'Olimex MOD-WIFI-ESP8266(-DEV)'.
1. Choose Tools > Port and select the appropriate port for your system setup.

#### Upload data and code

Unlike most Arduino projects, deployment takes two step.
This is because the project uses the ESP8266 file system called SPIFFS.
In the Arduino, uploading data is separate from code.

First put the ESP8266 in programming mode. This is usually via some buttons on the ESP8266 integration board.

In Ardnuio IDE:

1. Choose Tools > ESP8266 Sketch Data Upload.
1. Choose Sketch > Upload, or click the Upload toolbar button.

IMPORTANT! the data upload has to be done before the sketch upload

Remember that the FTDI supplies barely enough current to run WiFi.

## Testing

There are no unit tests, although it would be nice to do some simple ones for an arduino project.
There's also some Javascript logic that could be unit tested.

To aid in integration testing, there's a node server which simulates the ESP Web Server. It serves static
file directly from the data folder and provides a fake API. This is handy for testing and debugging the front end
code.

## Development

Use the Arduino IDE. Optionally, use a C++ IDE like Eclipse or IntelliJ.

### Arduino IDE

Library dependencires:
- ArduinoJson 5.13.5

Board dependencies
- esp8266 2.7.1 not 2.1.2

> try 2.5.1, 2.7.1 has weird python3 issue

### Using other IDEs

The Arduino IDE is quite adequate, but when your project grows, you may want additional developer capabilities such as:

- HTML editor
- SCM integration
- tree view source code navigation

When you use an external IDE and the Arduino IDE, it's recommend to set the Arduino IDE into "external Editor" mode.
In this mode, the Arduino IDE UI will disbale editing and automatically scan the file system for changes.

Preferences > use External Editor

### Arduino IDE command line

It is possible to run the Arduino toolchain from the command line, bypassing the Arduino IDE UI editor. More info
on this may be provided in the future.

## Links and references

https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/examples/FSBrowser/FSBrowser.ino

[ITEAD SONOFF Home Automation](https://www.itead.cc/smart-home.html)

## Notes

### Connecting to AP

- From your wireless device, connect to "ESP8266 Thing XXXX"
- The password is "sparkfun"
- Open a browser on http://192.168.41.1

