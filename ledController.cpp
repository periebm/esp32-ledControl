#include <Arduino.h>
#include <FastLED.h>
#include <EEPROM.h>
#include "ledController.h"

#define NUM_LEDS 60
#define DATA_PIN 26
#define COLOR_ORDER BRG
#define CHIPSET WS2811

CRGB leds[NUM_LEDS];

#define RED_ADDR_1 0
#define GREEN_ADDR_1 1
#define BLUE_ADDR_1 2

#define RED_ADDR_2 3
#define GREEN_ADDR_2 4
#define BLUE_ADDR_2 5

void ledConfig() {
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  loadLEDColorFromEEPROM();
}

void loadLEDColorFromEEPROM() {
  Serial.print(EEPROM.read(RED_ADDR_1));
  Serial.print(EEPROM.read(GREEN_ADDR_1));
  Serial.print(EEPROM.read(BLUE_ADDR_1));

  uint8_t r = EEPROM.read(RED_ADDR_1);
  uint8_t g = EEPROM.read(GREEN_ADDR_1);
  uint8_t b = EEPROM.read(BLUE_ADDR_1);

  setAllLEDsRGB(r, g, b);
}

void setAllLEDsRGB(uint8_t r, uint8_t g, uint8_t b) {
  fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
  FastLED.show();

  EEPROM.write(RED_ADDR_1, r);
  EEPROM.write(GREEN_ADDR_1, g);
  EEPROM.write(BLUE_ADDR_1, b);
  EEPROM.commit();
}