/*
 * YOUR PROJECT DESCRIPTION
 */

// Load libraries
// Adafruit Display initialization
// Variables and Pins for temperature measurement
// Variables for set temperature
// Thermoelectric cooler variables and Pins
// Button pins to set temperature
// LED Pins and temperature happiness range

void setup() {
  // Initialize Adafruit display
  // Initialize pin modes for buttons, PWM for cooler, LEDs
}

void getTemperature() {
  // Read thermistor, calculate and store temperature
}

void setDisplay(int valueToSet, bool setpoint=false) {
  // Set the display with a value to set (integer)
  // Additionaly display 'S' if we are in set mode
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
  // Your main loop to hang everything together
}
