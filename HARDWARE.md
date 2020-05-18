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
 
 > The vendor provides variants with 3.3, 5, and 12 VDC output.
 
 - [Aliexpress](https://www.aliexpress.com/item/33021479220.html)
 
 ## Solid state relay
 A solid state relay (SSR) has some advantages over a contact and coil relay.
 There's no extra circuitry required, such as a buffer transistor, as would be for a relay with 100 mA or so coil current.
 The ESP8266 MCU can only drive up to about 30 mA. 
 Optically isolated SSRs protect the MCU from the 120/220 VAC line and can be activated with less than 10 mA.
 
 [IXYS CPC1998J](https://www.digikey.com/product-detail/en/ixys-integrated-circuits-division/CPC1998J/CLA368-ND/2561233).
 
 - 20-240 VAC
 - 5 A without heatsink
 - 5 mA control current
 - isolation 2500 VAC
 - a bit expensive - $8
 
 ## Assembly
 Here are some picture of the assembled unit.
 
 ![The internal components](/doc/housing.jpg)
 
 ![Complete assembly with cover off](/doc/cover-off.jpg)
 
 ## Links and references
 I was wondering how the YS-12V450A power module supplied 3.3 V. Someone has [reverse engineered a similar module](https://easyeda.com/sascha23095123423/thx208-stripped-version) and shows how the TL431 does it.
