/**
 * DIYstoX v0.1
 * Ari Cooper-Davis | cooper-davis.net
 * Released under GNU GPL v3.0
 */

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

class LDM {
  public:
    LDM(){}

    // Variables
    float measurement = 0.0;

    /**
     * Setup: open the serial port
     */
    void setup()
    {
      Serial1.begin(9600);
    }

    /**
     * Loop: listen to the LDM serial and fill the buffer
     */
    void loop()
    {
      // Build up message in buffer
      if (Serial1.available()) {
        this->last_byte = Serial1.read();
        for (int i=1; i<14; i++) {
          this->buffer[i-1] = this->buffer[i];
        }
        this->buffer[13] = this->last_byte;
      }

      // Detect measurement in buffer and log
      if (memcmp(this->buffer, this->trigger, 3) == 0) {
        for (int i=0; i<4; i++) {
          this->measurement += (long)this->buffer[i+3] << this->bitshift[i];
        }
        this->measurement /= 10000.0;
      }
      // Prevent triggering again for the same measurement
      buffer[0] = 0;
    }

  private:
    // Constants
    const int bitshift[4] = {24, 16, 8, 0};
    const byte trigger[3] = {65, 84, 68};
    // Variables
    byte last_byte;
    byte buffer[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
};