/*
 * This routine controls reads the thermistor
 * resistance via a voltage divider and returns
 * the result.
 * 
 * Result: Temperature by fitting to -25, 25, print
 *  via Serial Monitor
 */

// Load Adafruit libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Initialize the display as matrix
Adafruit_7segment matrix = Adafruit_7segment();

float resRef = 10.01;  // reference resistance (kOhm)
float resTherm;   // thermistor resistance (kOhm)
int nOfAvg = 5;   // number of measurements to average

int adcResValue;  // variable to store the ADC reading
int adcResPin = A0;  // Pin the thermistor reading is connected to (HEX)

// temperature determination via Steinhard-Hall equation
float fitParamA = 0.002785219503;  // fit parameter a
float fitParamB = 0.000241846138;  // fit parameter b
float fitParamC = 0.000000831227;  // fit parameter c
float temperature;  // Calculated temperature
float KtoC = 273.15;   // how to tranform Kelvin to Celsius

// Iterators, etc.
int it;   // an iterator to use

// Setup routine
void setup() {
  // initialize the display
  matrix.begin(0x70);
}

void set_display(int value, bool setpoint = false) {
  // See exercise 8: If float is given for value, 
  // it will be converted to an integer.

  // set a given value to the 7 segment display.
  matrix.print(value);

  // set the first location to "S" (5) if true - set point
  if (setpoint) {
    matrix.writeDigitNum(0, 5, false);
  }
  matrix.writeDisplay();
}

void loop() {
  adcResValue = analogRead(adcResPin);  // read thermistor

  // average nOfAvg times the reading
  resTherm = 0;
  for (it = 0; it < nOfAvg; it++) {
    resTherm += resRef / (float(1023) / float(adcResValue) - 1);  // Equation 3.8
  }
  resTherm /= nOfAvg;

  // calculate temperature - equation (3.9)
  temperature = 1 / (
      fitParamA + fitParamB * log(resTherm) + fitParamC * pow(log(resTherm),3)
    ) - KtoC;

  // write to display
  set_display(temperature);

  delay(500);  // make it update a bit slower...
}
