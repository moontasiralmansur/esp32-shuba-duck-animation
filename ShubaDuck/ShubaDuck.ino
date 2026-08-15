#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "frames.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Wire.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }
  display.clearDisplay();
  display.display();
}

// Helper to draw a frame stored in PROGMEM
void drawFrameFromPROGMEM(const unsigned char* framePtr) {
  // On ESP32 we can use drawBitmap directly with PROGMEM pointer
  display.drawBitmap(0, 0, framePtr, frameWidth, frameHeight, 1);
}

void loop() {
  for (uint16_t i = 0; i < frameCount; i++) {
    // read pointer from PROGMEM
    const unsigned char* ptr;
    memcpy(&ptr, &frames[i], sizeof(ptr));

    display.clearDisplay();
    drawFrameFromPROGMEM(ptr);
    display.display();
    delay(60); // adjust playback speed (ms)
  }
}
