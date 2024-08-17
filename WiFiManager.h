#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WebServer.h>

extern WebServer server;

void connectToWiFi(const char* ssid, const char* password);
void setupRoutes();
void getHealth();
void setColor();

#endif