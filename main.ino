#include <HTTPClient.h>
#include <WiFi.h>
#include <EEPROM.h>

#include "WiFiManager.h"
#include "ledController.h"

#include "config.h"

#define EEPROM_SIZE 6

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  connectToWiFi(ssid, password);

  setupRoutes();
  ledConfig();
}

void loop() {
  server.handleClient();
}
