/**
 * DIYstoX v0.1
 * Ari Cooper-Davis | cooper-davis.net
 * Released under GNU GPL v3.0
 */

#include "LDM.cpp"
#include "LED.cpp"

LED led;
LDM ldm;

// Colors
const int red[3] = {100, 0, 0};
const int orange[3] = {100, 65, 0};
const int green[3] = {0, 100, 0};
const int blue[3] = {0, 0, 100};

void setup() {
  led.setup();
  ldm.setup();
  Serial.begin(9600); // Debugging
}

void loop() {
  led.loop();
  ldm.loop();

  // Check for measurements and log to serial
  if (ldm.measurement != 0.0) {
    led.blink(green, 600, 2);
    Serial.println(ldm.measurement, 3);
    ldm.measurement = 0.0;
  }
}