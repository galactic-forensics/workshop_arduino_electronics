/*
   Toggle LEDs
   This routine toggles two LEDs every second
   from the main loop, a green and a red LED.
   Either the green LED is on and the red one
   off or vice verse. Toggling happens in a 
   separate `setLeds` subroutine which is called 
   with a `redOn` boolean variable.
*/

// Pin assignments
int redLed = 3;   // pin for red LED
int greenLed = 2;   // pin for green LED

// Variables
bool redOn = true;  // state red LED on, green off
int delayTime = 1000;  // delay time in ms

void setup() {
  // declare pins for LEDs as outputs
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}

void setLeds(bool redOn) {
  if (redOn) {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
  else {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  }
}

void loop() {
  // set redOn to the pre-defined state
  setLeds(redOn);

  // switch redOn for the next time in the loop
  redOn = !redOn;

  // wait for some time
  delay(delayTime);
}
