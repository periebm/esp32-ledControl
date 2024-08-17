#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

void ledConfig();
void setAllLEDsRGB(uint8_t r, uint8_t g, uint8_t b);
void loadLEDColorFromEEPROM();

#endif