This is a repo to support the FabLab workshop "Build an LED Pixel 'Wall'". In the workshop we will learn the basics of working with LED strips using Arduino as a controller, as well as how to address LEDs as a matrix.

[<img src="path/to/image.png">](https://jugendgruppe.cccgoe.de/pic/MateLight36c3.jpg)

As you might expect for a hackerspace, the project is open-source and documented on github [here](https://github.com/jaseg/matelight). Other clubs and other groups have also made spin-offs, such as [this one](https://jugendgruppe.cccgoe.de/projekte/matelight.html). Our goal beyond this workshop is to do the same by installing one in the cafe area at 42 Berlin.

So each time you have a soft drink, think of us and add your bottle to the wall! :clinking_glasses:

# Aims of Today's Workshop

1. Learn the basics of how LED strips work and how to control them using an Arduino
2. Laser-cut, solder and assemble a template, to allow the LEDs to be installed in the crate
3. Create code to display a simple animation on the crate

You are also welcome to take a side-trip into bottle cutting or other forms of fabrication, depending on your interest.

# LED Strip Basics

## Strip Type

For our projects today, we have a WS2811B reel of LEDs. In our case we chose this type of strip because:
- the LEDs are individually addressable
- each LED is the strip is multicolour (RGB)
- the strip is powered by +5V (making it great for using directly with an Arduino, which outputs +5V)

## Strip Length, Density and Waterproofing

When buying LED strips, they are often sold in the form `5m 60 IP30` or similar, where:
- 5m is the length of the strip in meters
- 60 refers to the number of LEDs per meter
   - Common options are 30, 60 or 144 LEDs per meter
- 5m x 60 = 300 LEDs in total
- IP30 is the 'ingress protection' rating for dust/waterproofing - in this case not-waterproof
	- IP30/IP65/IP67 are common values
	- IP65: Protected against low-pressure water jets from any direction
	- IP67: Can withstand temporary immersion in water up to 1 meter for 30 minutes

# Power Considerations

At first, when working with a small number of LEDs on the strip, we can provide power via USB to our Arduino e.g. from our PC's USB port or other source.

As the project increases in scale our power requirements also increase and we will need to use an external power supply. For a single crate, we need to power 24 LEDs and should be able to use a 9V 2A Arduino power supply. For more crates, we will need to reconsider our power supply again.

Drawing more power than we have available risks:
- dimming or inconsistent brightness of the LEDs
- damage to the Arduino board
- damage or trigger overcurrent protection on the computer's USB port

To get a rough idea of how many LEDs we can power from the power coming from a standard PC USB port, we can make the following calculations:
- Each WS2812B LED can draw up to 60mA at full brightness (20mA per color channel).
- When powered via USB, the Arduino's 5V pin can supply only about 400-500mA.
- 500mA (USB supply) / 60mA (per LED) ≈ 8.33 LEDs

# Cutting and Soldering Strips

LED strips can be cut with standard scissors. Some tips:
- Always cut the strip at the designated cutting points, usually marked by copper pads or scissor icons
- Longer spacings between LED sections can lead to voltage drop, potentially causing inconsistent brightness along the strip. Consider adding power injection points for longer runs
- Thicker wires (lower gauge) are better for carrying current over longer distances
- Ensure clean, strong solder joints. Poor connections can lead to flickering or non-functional sections
- Provide proper strain relief for soldered connections, especially for flexible installations, to prevent breaks due to movement

# Connecting a 

We will will start by just working with a strip of three LEDs. You will notice that there are three connection points on the strip, 5V, GND and DATA.

5V - is simply connected to the 5V output pin of the Arduino
GND - is simply connectd to one of the two GND pins of the Arduino
DATA - typically goes to any digital pin on the Arduino e.g. A0

# Basic Code Examples

We use the FastLED library to programatically address the LEDs on the strip. This it not the only LED library out there - feel free to experiment :)

## Hello World

3 LED's of same colour example:

```
#include <FastLED.h>

#define LED_PIN 0
#define NUM_LEDS 3

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50); // Set initial brightness (0-255)
}

void loop() {
  // Example: Set each led to a different color and brightness
  for (int led = 0; led < NUM_LEDS; led++) {
    setLedColor(led, CHSV(random8(), 255, random8(64, 255)));
  }
  
  FastLED.show();
  delay(1000);  // Wait for 1 second1 before changing colors
}

void setLedColor(int ledIndex, CHSV color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
}
```

## N x N Matrix Example

In the example below we provide code for a N x N matrix of LEDs. This comes from when we thought the bottles would need more than one LED inside to be bright enough. You can adapt this code to your needs.

```
#include <FastLED.h>

#define LED_PIN     0
#define NUM_BOTTLES 2  // 4x4 matrix
#define LEDS_PER_BOTTLE 3
#define NUM_LEDS    (NUM_BOTTLES * LEDS_PER_BOTTLE)

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);  // Set initial brightness (0-255)
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
```

# Scaling up the project - open questions

## Power Requirements

What kind of power supply would we need for powering a bigger wall, for example a matrix of 4 x 3 crates?

## Timing

In the C-Base Mate Light, they use WS2801 strips instead of our WS2812B. This is because the WS2801 uses a separate clock line, which allows for more precise timing and higher data rates. This makes it less susceptible to timing issues that can affect WS2812B strips. But it means we have to redesign for four wires rather than three.

## Do we need 'strips' at all?

In other version of the projects, they use individual LEDs soldered onto custom PCBs installed in the cap. So maybe in future we could do this or just solder to the LEDs directly...

[<img src="path/to/image.png">](https://jugendgruppe.cccgoe.de/pic/MateLight-PlatinenHaufen.jpg)