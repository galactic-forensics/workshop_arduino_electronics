/*
 * Thermoelectric cooler control circuit
 * Step 1
 * 
 * Currently implemented:
 * - get the current temperature from the thermistor
 * - display the temperature on the 7segment display
 * - button control (with external pull-down resistors) for setMode
 * - thermoelectric cooler is implemented in on/off logic
 * - implemented green LED that will light up if we are close to setPoint
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
int setPoint = 15;  // set temperature in C.
bool setModeToggle = false;  // Start with setMode deactivated

int maxSetTemp = 25;
int minSetTemp = -10;

// Thermoelectric cooler variables and Pins
const int controlPinTEC = 11;  // use PWM pin for future development

// Button pins to set temperature
const int setModeButton = 4;
const int setPlusButton = 5;
const int setMinusButton = 6;

int buttonInteractionTime = 250;  // human interaction time in ms with buttons

// LED Pins and temperature happiness range
const int ledOk = 9;
float happiness_delta = 0.5;  // +- this delta, our unit is running great!

void setup() {
  // Initialize Adafruit display
  matrix.begin(0x70);
  
  // Initialize pin modes for buttons, PWM for cooler, LEDs
  pinMode(setModeButton, INPUT);
  pinMode(setPlusButton, INPUT);
  pinMode(setMinusButton, INPUT);
  pinMode(controlPinTEC, OUTPUT);
  pinMode(ledOk, OUTPUT);
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
  
  // check if set mode button is pressed and toggle setMode
  if (digitalRead(setModeButton) == HIGH) {
    setModeToggle = !setModeToggle;
    delay(buttonInteractionTime);
  }

  bool buttonWasPressed = false;  // bool to check if a button was pressed

  // adjust set point dependent on button presses
  if (setModeToggle){  // only do stuff if we are in set mode
    
    if (digitalRead(setPlusButton) == HIGH) {  // plus button is pressed
      if (setPoint < maxSetTemp) {  // only do something if we are not at the maximum level yet
        setPoint += 1;
      }
      buttonWasPressed = true;  // make sure we delay for human interaction time later
    }

    if (digitalRead(setMinusButton) == HIGH) {  // minus button is pressed
      if (setPoint > minSetTemp) {  // only do something if we are not at the minimum level yet
        setPoint -= 1;
      }
      buttonWasPressed = true;  // make sure we delay for human interaction time later
    }
  }

  if (setModeToggle) {  // set the display if we are in set mode with the setPoint
    setDisplay(setPoint, true);
  }

  if (buttonWasPressed) {  // delay if a button was pressed. do this here for fast display update
    delay(buttonInteractionTime);
  }
}

void controlTEC() {
  // Control the termoelectric cooler.
  if (currentTemperature > float(setPoint)) {  // it's too warm
    digitalWrite(controlPinTEC, HIGH);
  }
  else {  // it's just right or too cold
    digitalWrite(controlPinTEC, LOW);
  }
}

void checkTemperatureOk() {
  // If temperature in given range, turn green LED on
  float actual_delta = abs(float(setPoint) - currentTemperature);
  if (actual_delta <= happiness_delta) {  // everything is great
    digitalWrite(ledOk, HIGH);
  }
  else {  // we are not in our required temperature zone
    digitalWrite(ledOk, LOW);
  }
}

void loop() {
  // Get and display temperature when not in setMode
  getTemperature();
  if (!setModeToggle) {
    setDisplay(round(currentTemperature), false);
  }

  controlTEC();  // run after getTemperature to not have delays in regulating

  checkTemperatureOk();  // turn green LED on if all is well

  setMode();  // Handles all the setMode functions!
}
