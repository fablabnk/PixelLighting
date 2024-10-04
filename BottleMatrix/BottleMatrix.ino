#include <FastLED.h>

#define LED_PIN     0
#define NUM_BOTTLES 2  // 4x4 matrix
#define LEDS_PER_BOTTLE 3
#define NUM_LEDS    (NUM_BOTTLES * LEDS_PER_BOTTLE)

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);  // Set initial brightness (0-255)
}

void loop() {
  // Example: Set each bottle to a different color and brightness
  for (int bottle = 0; bottle < NUM_BOTTLES; bottle++) {
    setBottleColor(bottle, CHSV(random8(), 255, random8(64, 255)));
  }
  
  FastLED.show();
  delay(2000);  // Wait for 2 seconds before changing colors
}

void setBottleColor(int bottleIndex, CHSV color) {
  int startLED = bottleIndex * LEDS_PER_BOTTLE;
  for (int i = 0; i < LEDS_PER_BOTTLE; i++) {
    leds[startLED + i] = color;
  }
}