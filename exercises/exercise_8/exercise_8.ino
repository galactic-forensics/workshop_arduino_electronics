/*
 * This subroutine controls an adafruit 7 segment display
 * with backpack. The display is controlled via a
 * subroutine, while the loop can randomly send information 
 * to it.
 * 
 * We are using the adafruit libraries for this display.
 */

// Load Adafruit libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Initialize the display as matrix
Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  // initialize the display
  matrix.begin(0x70);
}

void set_display(int value, bool setpoint = false) {

  // set a given value to the 7 segment display
  matrix.print(value);

  // set the first location to "S" (5) if true - set point
  if (setpoint) {
    matrix.writeDigitNum(0, 5, false);
  }
  matrix.writeDisplay();
}

void loop() {
  // display numbers from the exercise, 1 second delay
  
  set_display(-9);
  delay(1000);

  set_display(20);
  delay(1000);
  
  set_display(-10, true);
  delay(1000);
}
