/*
 * Thermoelectric cooler control circuit
 * Step 1
 * 
 * Currently implemented:
 * - get the current temperature from the thermistor
 * - display the temperature on the 7segment display
 */

// Load libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Adafruit Display initialization
Adafruit_7segment matrix = Adafruit_7segment();


// Variables and Pins for temperature measurement
float currentTemperature;  // current temperature (Celsius)

int numOfAverages = 5;  // averages to take for temperature measurement
float resReference = 10.01;  // Reference resistor in kOhm

const int adcPinTemp = A0;  // Pin for ADC measurement

const float fitParamA = 0.002785219503;  // fit parameter a
const float fitParamB = 0.000241846138;  // fit parameter b
const float fitParamC = 0.000000831227;  // fit parameter c
const float KtoC = 272.15;  // how to convert Kelvin to Celsius

// Variables for set temperature
// Thermoelectric cooler variables and Pins
// Button pins to set temperature
// LED Pins and temperature happiness range

void setup() {
  // Initialize Adafruit display
  matrix.begin(0x70);
  
  // Initialize pin modes for buttons, PWM for cooler, LEDs
}

void getTemperature() {
  // Read thermistor, calculate and store temperature

  // read ADC value numOfAverages times and add up.
  int adcReadValue = 0;
  for (int it = 0; it < numOfAverages; it++) {
    adcReadValue += analogRead(adcPinTemp);  // read ADC value
    delay(10);  // wait 10 ms before the next measurement
  }
  // calculate average
  float adcAvg = float(adcReadValue) / float(numOfAverages);
  // calculate resistance of thermistor, equation (3.8)
  float resTherm = resReference / (1023 / adcAvg - 1);
  // calculate temperature, equation (3.9)
  currentTemperature = 1 / (
      fitParamA + fitParamB * log(resTherm) + fitParamC * pow(log(resTherm), 3)
    ) - KtoC;
}

void setDisplay(int valueToSet, bool setpoint=false) {
  // Set the display with a value to set (integer)
  // Additionaly display 'S' if we are in set mode
  matrix.print(valueToSet);  // print the given value, an integer

  // if the setpoint boolean is true, then write an "S" (5) into first digit.
  if (setpoint){
    matrix.writeDigitNum(0, 5, false);
  }

  matrix.writeDisplay();  // display what we just did
}

void setMode() {
  // Check if we are in set mode and adjust display
  // If in set mode, adjust set point if called for
}

void controlTEC() {
  // Control the termoelectric cooler.
}

void checkTemperatureOk() {
  // If temperature in given range, turn green LED on
}

void loop() {
  getTemperature();

  setDisplay(round(currentTemperature), false);  
  
  delay(500);  // make it a touch slower
}
