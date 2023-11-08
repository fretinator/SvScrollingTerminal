#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "secrets.h"
#include "DebugUtil.h"
#include "ANSITerminal.h"
#include "M5StackKeyboard.h"
#include "ILI9341SpiRenderer.h"



DebugUtil logger = DebugUtil(DEBUG, &Serial);

WiFiClient netClient;
#define MAX_WIFI_ATTEPTS 10
const int net_retries = 3;


// Screen for this project - M5Stack Core TFT
ILI9341SpiRenderer screen = ILI9341SpiRenderer(uint8_t(1), TermColor::ESC_BLACK, 
  TermColor::ESC_WHITE, &logger);

M5StackKeyboard keyboard = M5StackKeyboard(&logger);
ANSITerminal terminal = ANSITerminal(&keyboard, &screen, &netClient, &logger);

bool setupWiFi() {
  uint8_t curAttempts = 0;

  Serial.println("WiFi connection starting.\n\t");

  WiFi.begin(my_ssid, my_password);
  
  int ms_delay = 500;

  while (curAttempts < MAX_WIFI_ATTEPTS && WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(ms_delay);
    Serial.print(".");
    WiFi.begin(my_ssid, my_password);
    curAttempts++;
    ms_delay += 500;
  }

  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection failed.");
    return false;
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
  return true; 
}

bool connectToHost() {
  IPAddress addr;
  addr.fromString(host);
  return netClient.connect(addr, port);
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  logger.debug("Starting main application");


  if(!keyboard.init()) {
    String msg = "Error initializing keyboard, abort app.";
    logger.error(msg);
    screen.printString(msg, 0, 0);
    while(true);
  }
  

  if(!screen.init()) {
    String msg = "Error initializing screen, abort app.";
    logger.error(msg);
    while(true);
  }


  if(!setupWiFi()) {
    String msg = "Unable to connect to WiFi, abort app.";
    logger.error(msg);
    screen.printString(msg, 0, 0);
    delay(100);
    while(true);
  }

  if(!connectToHost()) {
    String msg = "Unable to connect to Host, abort app.";
    logger.error(msg);
    screen.printString(msg, 0, 0);
    delay(100);
    while(true);
  }

  // These are only meaningful after the screnn 
  // has been initialized.
  uint16_t rows = screen.getRows();
  uint16_t cols = screen.getCols();


  if(!terminal.init(rows, cols)) {
    String msg = "Error initializing terminal, abort app.";
    logger.error(msg);
    screen.printString(msg, 0, 0);
    while(true);    
  }

  screen.setBackColor(TermColor::ESC_BLACK);
  screen.setTextColor(TermColor::ESC_WHITE);
  screen.printString("Net terminal", 1, 18);

  delay(3000);

  screen.clearScreen();;

  logger.debug("Entering terminal loop,,,");
}

void loop() {
  terminal.loop();
}
