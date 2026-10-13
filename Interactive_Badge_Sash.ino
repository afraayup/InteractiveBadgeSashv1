
#include <Adafruit_CircuitPlayground.h>

// pressure sensor pins
const int buttons[4] = {A4, A5, A6, A7};

// badge colours
const uint32_t colors[4] = {
  0x8000FF,  // Butterfly: Purple
  0xFFFF00,  // Pig: Yellow
  0x0066FF,  // Camping: Blue
  0xFF0000   // First aid: Red
};

// musical tones
const int notes[4] = {
  262,  // Butterfly: C4
  330,  // Pig: E4
  392,  // Camping: G4
  523   // First aid: C5
};

int activeButton = -1;

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(40);
  CircuitPlayground.clearPixels();

  // Set up pressure sensors
  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {
  int pressed = -1;

  // Check each pressure sensor
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttons[i]) == LOW) {
      pressed = i;
      break;
    }
  }

  // Respond to a new press or release
  if (pressed != activeButton) {
    activeButton = pressed;
    CircuitPlayground.clearPixels();

    if (activeButton >= 0) {

      // Play unique tone
      CircuitPlayground.playTone(
        notes[activeButton], 150
      );

      // Light LEDs sequentially
      for (int led = 0; led < 10; led++) {

        if (digitalRead(buttons[activeButton]) == HIGH) {
          break;
        }

        CircuitPlayground.setPixelColor(
          led, colors[activeButton]
        );

        delay(60);
      }
    }
  }

  delay(20);
}
