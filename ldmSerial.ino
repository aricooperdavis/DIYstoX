/*
 *  This file takes readings from the LDM, converts them into m, and adds them to a queue for sending.
 *  When Serial (USB) is available it then sends those readings one by one in chronological order.
 */

static byte b;
static byte trigger[3];
static byte payload[4];
static int p = 0;
static float values[30];
static int v = 0;
static bool measure = false;
static byte ATD[] = {65, 84, 68};

void setup() {  
  // Set LED pin to output
  pinMode(LED_RED, OUTPUT);

  // Open serial port for connection to computer  
  Serial.begin(57600);
  // Open serial port for connection to LDM
  Serial1.begin(9600);
}

void _end_measurement() {
  /*
   * Perform functions required once a measurement completes succesfully.
   */

  // Convert byte array to float in meters and add to array
  values[v] = (((long)payload[0] << 24)
            + ((long)payload[1] << 16)
            + ((long)payload[2] << 8)
            + (long)payload[3]) / 10000.0;
  v += 1;

  // Reset payload variables to all zeros
  for (int i = 0; i < 4; i++){
    payload[i] = 0;
  }
  p = 0;
  measure = false;
}

bool _update_trigger(byte b) {
  /*
    Add a character to the trigger. If the trigger becomes
    ATD return true, otherwise return else false.
   */

  // Update trigger
  trigger[0] = trigger[1];
  trigger[1] = trigger[2];
  trigger[2] = b;

  // Check if trigger is ATD
  if (memcmp(trigger, ATD, 3) == 0) {
    return true;
  }
  else {
    return false;
  }
}

void _get_measurement() {
  if (Serial1.available() > 0) {

    // Read a character from the LDM serial
    b = Serial1.read();

    // If currently taking a measurement...
    if (measure) {
      // ...end the measurement if the buffer has been filled...
      if (p == 4) {
        _end_measurement();
      }
      // ...otherwise add the character to the end of the distance...
      else {
        payload[p] = b;
        p++;
      }
    }
    // If not currently taking a measurement...
    else {
      measure = _update_trigger(b);
    }
  }
}

void _send_measurement() {
  if (v > 0) {
    if (Serial) {
      Serial.println(values[0], 3);
      v -= 1;
      
      for (int i = 0; i < 29; i++) {
        values[i] = values[i+1];
        values[29] = 0;
      }
    }
  }
}

void loop() {
  _get_measurement();
  _send_measurement();
}
