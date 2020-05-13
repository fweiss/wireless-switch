# Hardware
A summary of the hardware components used for the wireless switch

- MCU
- MCU power supply
- solid state relay
- outlet
- line cord
- enclosure
- miscellaneous

## MCU
Olimex ESP8266
 
 ## MCU power
 - Provide 3.3 VDC from 120-240 VAC mains
 - min current ?
 - small size
 - safety
 - isolation
 
 YS-12V450A
 - [Aliexpress](https://www.aliexpress.com/item/33021479220.html)
 
 ## Solid state relay
 A relay would require a buffer circuit because they require about 100 mA to activate while the MCU can only drive up to about 30 mA. SSRs are availalable that both isolate the MCU from the 120/220 VAC line and can be activated with less than 10 mA.
 
 IXYS CPC1998J
 - 20-240 VAC
 - 5 A without heatsink
 - 5 mA control current
 - isolation 2500 VAC
 - a bit expensive - $8
 
 ## Assembly
 Here are some picture of the assembled unit.
 
 ![The internal components](/doc/housing.jpg)
 
 ![Complete assembly with cover off](/doc/cover-off.jpg)
