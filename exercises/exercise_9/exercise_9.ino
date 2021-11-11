/*
 * This routine controls reads the thermistor
 * resistance via a voltage divider and returns
 * the result.
 * 
 * Result: Resistance transferred via SerialMonitor
 */

float resRef = 10.01;  // reference resistance (kOhm)
float resTherm;   // thermistor resistance (kOhm)

int adcResValue;  // variable to store the ADC reading
int adcResPin = A0;  // Pin the thermistor reading is connected to (HEX)


void setup() {
  Serial.begin(9600);  // initialize serial monitor

}

void loop() {
  adcResValue = analogRead(adcResPin);  // read thermistor

  // careful in the next step: make sure the ADC value division
  // takes place as floats! otherwise you might get rounding issues.
  resTherm = resRef / (float(1023) / float(adcResValue) - 1);  // Equation 3.8

  Serial.print("Resistance (kOhm): ");
  Serial.println(resTherm);
}
