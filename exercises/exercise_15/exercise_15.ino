/*
 * Controll the thermoelectric cooler (TEC) via PWM pin.
 * PWM pin takes 0 to 255, we will map this from 0 to 100\%.
 * 
 * Note the usage of the map function, see here for detail:
 * https://www.arduino.cc/reference/en/language/functions/math/map/
 */

int controlPin = 11;  // pin to control the MOSFET
int powerLevel = 25;  // power level in percent

void setup() {
  pinMode(controlPin, OUTPUT);

}


void controlTEC() {
  // Analog write to the control pin with the given power Level.
  int pwmOutput = map(powerLevel, 0, 100, 0, 255);  // map the power level
  analogWrite(controlPin, pwmOutput);

}


void loop() {
  // call the control routine, then wait 3 seconds
  controlTEC();
  delay(3000);
}
