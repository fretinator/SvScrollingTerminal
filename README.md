# SvScrollingTerminal
A basic ANSI-like terminal with Hardware Scrolling, basic color and screen position support.

Developed with Huzzah Esp32 V2 Feather connected to the 2.4-inch TFT Featherwing. The I2C kepboard is the M5Stack keyboard.

My goal, besides finally getting hardware verical scrolling working, we to develop using Abstract Classes so a different screen or keyboard can be swapped by creating classes that inherit the ScreenRenderer or KeyboardHandler classes. 

The ILI9341 worked well with hardware scrolling and the Adafruit_ILI9341 library simplified the scroll imiplmentation.

NOTE: You must inlucde a secrets.h with this information:

#ifndef SECRETS_H

#define SECRETS_H

const String host = "Server IP"; // Example 192.168.1.233

const int port = ####; // Example 8080

const char* my_ssid = "Wifi ESSID"; // Replace with you WiFi network name

const char* my_password = "WIF PASSWORD"; // Replace with your WiFi password

#endif
