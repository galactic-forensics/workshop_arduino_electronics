/*
 * Controll the thermoelectric cooler (TEC) via PWM pin.
 * PWM pin takes 0 to 255, we will map this from 0 to 100\%.
 * 
 * Display the temperature on the LCD screen.
 * 
 * Here we are reusing the temperature code from previous exercises!
 */

// Load Adafruit libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Cooler setup and global variables
int controlPin = 11;  // pin to control the MOSFET
int powerLevel = 100;  // power level in percent

// Display
Adafruit_7segment matrix = Adafruit_7segment();

// Temperature measurement setup
float resRef = 10.01;  // reference resistance (kOhm)
float resTherm;   // thermistor resistance (kOhm)
int nOfAvg = 3;   // number of measurements to average

int adcResValue;  // variable to store the ADC reading
int adcResPin = A0;  // Pin the thermistor reading is connected to (HEX)

// temperature determination via Steinhard-Hall equation
float fitParamA = 0.002785219503;  // fit parameter a
float fitParamB = 0.000241846138;  // fit parameter b
float fitParamC = 0.000000831227;  // fit parameter c
float temperature;  // Calculated temperature
float KtoC = 273.15;   // how to tranform Kelvin to Celsius


void controlTEC() {
  // Analog write to the control pin with the given power Level.
  int pwmOutput = map(powerLevel, 0, 100, 0, 255);  // map the power level
  analogWrite(controlPin, pwmOutput);

}


void setup() {
  // pins
  pinMode(controlPin, OUTPUT);

  // initialize the display
  matrix.begin(0x70);

  // control the TEC()
  controlTEC();
}


void getTemperature() {
  // Read the temperature and set temperature variable
  adcResValue = analogRead(adcResPin);  // read thermistor
  
  // average nOfAvg times the reading
  resTherm = 0;
  for (int it = 0; it < nOfAvg; it++) {
    resTherm += resRef / (float(1023) / float(adcResValue) - 1);  // Equation 3.8
  }
  resTherm /= nOfAvg;

  // calculate temperature - equation (3.9)
  temperature = 1 / (
      fitParamA + fitParamB * log(resTherm) + fitParamC * pow(log(resTherm),3)
    ) - KtoC;
}


void setDisplay(int value, bool setpoint = false) {
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
  // display temperature and update every second
  getTemperature();
  setDisplay(temperature);
  delay(3000);
}
