# SvScrollingTerminal
A basic ANSI-like terminal with Hardware Scrolling, basic color and screen position support.

Developed with Huzzah Esp32 V2 Feather connected to the 2.4-inch TFT Featherwing. The I2C kepboard is the M5Stack keyboard.

My goal, besides finally getting hardware verical scrolling working, we to develop using Abstract Classes so a different screen or keyboard can be swapped in a classes created that inherit the ScreenRenderer or KeyboardHandler classes. 

The ILI9341 worked well with hardware scrolling and the Adafruit_ILI9341 library simplified scrolling.
