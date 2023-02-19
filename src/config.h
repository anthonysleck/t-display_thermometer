#ifndef config_h
#define config_h

// system versioning
#define VER "0.1"
#define VER_BUILD "12222022"
#define email "anthony.sleck@gmail.com"
#define firmwareLink "https://github.com/anthonysleck/t-display_thermometer"

// common includes
#include <Arduino.h>
#include <AsyncElegantOTA.h>
#include <AsyncTCP.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "webpages.h"
#include <WiFi.h>
#include <WiFiClient.h>

// server configs
AsyncWebServer server(80);

// DHT setup
#define DHTPIN 2
#define DHTTYPE DHT11

// TFT config
#define TFT_BLACK 0x0000 // black
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

// wd timer
unsigned long startPostMillis;
const unsigned long periodPost = 300000;     // the time in ms
#define WATCHDOG_TIMEOUT_S 15   // enter time in sec
hw_timer_t * watchDogTimer = NULL;

// WiFi settings
const char *ssid = "SLEMPSONRACING";     // enter your SSID here
const char *password = "NotForYou"; // enter password here

#endif