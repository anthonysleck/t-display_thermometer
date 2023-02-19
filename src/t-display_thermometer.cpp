/*
   ESP32 Temperature Monitor with T-Display
   Description:
   Notes:
   -Coming Soon!
   Contact Info:
   email - anthony.sleck@gmail.com
   web - anthony.sleck.us
   github - https://github.com/anthonysleck
   Changelog:
   0.1 - new code
*/

// includes
#include "config.h"

// variables
float sensor_temperature, sensor_humidity, sensor_pressure, ds_temperature;
DHT dht(DHTPIN, DHTTYPE);

String readDHTemperature()
{
    // start DHT
  float espTemperature = dht.readTemperature(true);
  if (isnan(espTemperature)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "0.0";
  }
  else {
    Serial.println(espTemperature);
    return String(espTemperature);
  }
}

String processor(const String &var)
{
  if (var == "ESPTEMPERATURE")
  {
    return readDHTemperature();
  }
  return String();
}

void IRAM_ATTR watchDogInterrupt()
{
  Serial.println("reboot");
  ESP.restart();
}

void watchDogRefresh()
{
  timerWrite(watchDogTimer, 0);   //reset timer
}

void startWatchdogTimer()
{
  Serial.println("Starting watchdog timer!");
  watchDogTimer = timerBegin(2, 80, true);
  timerAttachInterrupt(watchDogTimer, &watchDogInterrupt, true);
  timerAlarmWrite(watchDogTimer, WATCHDOG_TIMEOUT_S * 1000000, false);
  timerAlarmEnable(watchDogTimer);
  Serial.println("Watchdog timer started!");
}

void WiFiConnect()
{
  Serial.println();
  Serial.println();
  Serial.print("Starting WIFI AP with SSID of ");
  Serial.println(ssid);
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void rootServer()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html, processor); });
             
  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", temp_html, processor); });

  server.on("/esptemperature", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", readDHTemperature().c_str()); });

  // start ElegantOTA
  AsyncElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started");
}

void start_tft()
{
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0, 0);
}

void display_tft()
{
  IPAddress IP = WiFi.softAPIP();
  
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 18, 2);
  tft.setTextColor(TFT_GOLD,TFT_BLACK);
  tft.setTextSize(1);
  tft.println("Temperature is: ");

  tft.setCursor(125, 8, 2);
  tft.setTextColor(TFT_GOLD,TFT_BLACK);
  tft.setTextSize(2);
  tft.println(readDHTemperature().c_str());

  tft.setCursor(5, 50, 2);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextSize(1);
  tft.println("IP Address is: ");

  tft.setCursor(98, 50, 2);
  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.setTextSize(1);
  tft.println(IP);

  tft.setCursor(5, 75, 2);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextSize(1);
  tft.println("SSID: ");

  tft.setCursor(98, 75, 2);
  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.setTextSize(1);
  tft.println(ssid);

  tft.setCursor(5, 100, 2);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextSize(1);
  tft.println("Password: ");

  tft.setCursor(98, 100, 2);
  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.setTextSize(1);
  tft.println(password);
}

void setup()
{
  delay(5000);

  // start serial
  Serial.begin(115200);

  // print sketch information
  Serial.println("Created by Anthony Sleck");
  Serial.println("Email at anthony.sleck@gmail.com");
  Serial.print("Version ");
  Serial.println(VER);
  Serial.print("Build Code ");
  Serial.println(VER_BUILD);
  Serial.print("Github: ");
  Serial.println(firmwareLink);
  
  // start DHT
  dht.begin();
  
  // start WiFi
  WiFiConnect();

  // start server
  rootServer();

  // start tft
  start_tft();

  // start watchdog timer
  startWatchdogTimer();
}

void loop()
{
  // update the TFT display
  display_tft();
  
  // add a quick delay
  delay(1000);
  
  // reset watchdog timer
  watchDogRefresh();
}