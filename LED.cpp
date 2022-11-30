/**
 * DIYstoX v0.1
 * Ari Cooper-Davis | cooper-davis.net
 * Released under GNU GPL v3.0
 */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class LED {
  public:
    LED(){}

    /**
     * Setup: intialise the neopixel
     */
    void setup()
    {
      this->neopix.begin();
      this->neopix.setPixelColor(this->color, 0);
      this->neopix.show();
    }
    
    /**
     * Loop: keep the LED doing what it should be doing (such as blinking or being solid)
     */
    void loop() {
      if (this->blink_state || this->solid_state){
        
        this->now = millis();
        // Turn LED off if finished
        if (this->now > this->end_at) {
          this->neopix.clear();
          this->blink_state = 0;
          this->solid_state = 0;
        } else {

          // Blink LED if required
          if (this->blink_state) {
            int period = (this->blink_state == 1) ? 300 : 100;
            // LED should be lit if !((end_at-now-1)//period)%2
            int div = (this->end_at-this->now-1)/period;
            if (div%2) {
              this->neopix.clear();
            } else {
              this->neopix.setPixelColor(0, this->color);
            }
          }
        }

        this->neopix.show();
      }
    }

    /**
     * Solid: set the LED to be a solid color for a duration
     */
    void solid(int color[3], int dur_ms)
    {
      this->color = neopix.Color(color[0], color[1], color[2]);
      this->end_at = millis()+dur_ms;
      this->solid_state = 1;
      this->blink_state = 0;
      
      // Turn LED on
      this->neopix.setPixelColor(0, this->color);
      this->neopix.show();
    }

    /**
     * Blink: have the LED blink at a set speed for a duration
     */
    void blink(const int color[3], int dur_ms, int rate)
    {
      this->color = neopix.Color(color[0], color[1], color[2]);
      this->end_at = millis()+dur_ms;
      this->blink_state = rate;
      this->solid_state = 0;
    }

  private:
    // Variables
    Adafruit_NeoPixel neopix = Adafruit_NeoPixel(1, PIN_NEOPIXEL);
    long now = 0;
    long end_at = 0;
    int blink_state = 0;
    int solid_state = 0;
    uint32_t color = 0;
};