# Questions

- Do we have a more powerful PSU in the lab for making a bigger wall?

# Common challenge

Your group challenge for today's workshop is to create a 3x3 bottle matrix using LED strips, where:

1. freestanding
1. Your final prototype should be able to display a simple repeating animation
2. Each set of LEDs should be individually addressable in matrix form
3. each bottle should contain a strip of 3 LEDs

# LED Info

For the project today, we have a `5m 60 IP30` WS2811B reel of LEDs, where:

	- WS2811B refers to the type of strip, in our case we chose this strip because:
		- the LEDs are individually addressable
		- each LED is the strip is multicolour (RGB)
		- the strip is powered by +5V (making it great for using directly with an Arduino)

	- 5m is the length of the strip in meters
	- 60 refers to the number of LEDs per meter
		- common options are 30/60/144
	- 5m x 60 = 300 LEDs in total
	- IP30 is the 'ingress protection' rating for dust/waterproofing - in this case not-waterproof
		- IP30/IP65/IP67 are common values
		- IP65: Protected against low-pressure water jets from any direction
		- IP67: Can withstand temporary immersion in water up to 1 meter for 30 minutes

# Power Considerations

At the project increases in scale the power requirements also increase and will require extra consideration. At first, when working with a single 3-LED strip, we can provide power from our PC USB power to our Arduino. But this will only take us so far. Beyond that we risk:

- Dimming or inconsistent brightness of the LEDs
- Damage to the Arduino board
- Damage or trigger overcurrent protection on the computer's USB port

To get a rough idea of how many LEDs we can power from the power coming from a standard PC USB port, we can make the following calculations:
- Each WS2812B LED can draw up to 60mA at full brightness (20mA per color channel).
- When powered via USB, the Arduino's 5V pin can supply only about 400-500mA.
- 500mA (USB supply) / 60mA (per LED) ≈ 8.33 LEDs

So we can see that when we get beyond two 3-LED strips, it's time to start using a standard 9V 1A Arduino power supply.

And when we get beyond 15-20 LEDs (3 x 3 x 3 = 27 LEDs), we will need something more powerful still.

# Cutting and Soldering

- Always cut the strip at the designated cutting points, usually marked by copper pads or scissor icons

- Longer spacings between LED sections can lead to voltage drop, potentially causing inconsistent brightness along the strip. Consider adding power injection points for longer runs

- Thicker wires (lower gauge) are better for carrying current over longer distances

- Ensure clean, strong solder joints. Poor connections can lead to flickering or non-functional sections

- Provide proper strain relief for soldered connections, especially for flexible installations, to prevent breaks due to movement

# Project Phases

## 1. Solo strip

You will start by just working with the section of 

(3 LEDs) and trying to get this to

You will notice that there are three connection points on the strip, 5V, GND and DATA.

5V - is simply connected to the 5V output pin of the Arduino
GND - is simply connectd to one of the two GND pins of the Arduino
DATA - typically goes to any digital pin on the Arduino e.g.

## 2. 2 x Connected strips

Once you have one strip working, it's time to try connecting two and addressing them as a chain. This will be a chance to sharpen your soldering skills!

## 3. 3 x Connected strips in bottles (a row)

once we have two bottles, we can just

## 4. Making two more rows


# Basic Code Example

3x3 matrix example:

```
#include <FastLED.h>

#define NUM_ROWS 3
#define NUM_COLS 3
#define NUM_LEDS (NUM_ROWS * NUM_COLS)
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(128); // 0-255
}

void loop() {
  // Example: Set each "pixel" to a different color
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      int index = row * NUM_COLS + col;
      leds[index] = CHSV(random(256), 255, 255);
    }
  }
  FastLED.show();
  delay(1000);
}

// Function to set color of a specific "pixel"
void setPixel(int row, int col, CRGB color) {
  int index = row * NUM_COLS + col;
  leds[index] = color;
}
```

# Extending the Project

Experimenting with other forms
Side-trip into bottle cutting
Stackable opaque boxes
Hacking and upcycling existing LED devices
Flash the fridge!