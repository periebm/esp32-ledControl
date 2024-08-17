#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#include "WiFiManager.h"
#include "ledController.h"

WebServer server(80);

void connectToWiFi(const char* ssid, const char* password) {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Failed to connect to WiFi.");
  }
}

void setupRoutes() {
  server.on("/health", getHealth);
  server.on("/setColor", HTTP_POST, setColor);

  server.begin();
  Serial.println("HTTP server started");
}

void getHealth() {
  StaticJsonDocument<200> doc;
  doc["status"] = "ok";
  doc["message"] = "Server is running";

  String response;
  serializeJson(doc, response);

  server.send(200, "application/json", response);
}

void setColor() {
  if (server.hasArg("plain")) {
    String jsonData = server.arg("plain");

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonData);

    if (error) {
      doc["message"] = "Invalid JSON";

      String response;
      serializeJson(doc, response);
  
      server.send(400, "application/json", response);
      return;
    }

    int r = doc["r"];
    int g = doc["g"];
    int b = doc["b"];

    r = constrain(r, 0, 255);
    g = constrain(g, 0, 255);
    b = constrain(b, 0, 255);

    setAllLEDsRGB(r, g, b);

    server.send(200, "text/plain", "LED color updated");
  } else {
    server.send(400, "text/plain", "Body not found");
  }
}