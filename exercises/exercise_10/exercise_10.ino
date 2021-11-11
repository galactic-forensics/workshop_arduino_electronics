/*
 * This routine controls reads the thermistor
 * resistance via a voltage divider and returns
 * the result.
 * 
 * Result: Temperature by fitting to -25, 25, print
 *  via Serial Monitor
 */

float resRef = 10.01;  // reference resistance (kOhm)
float resTherm;   // thermistor resistance (kOhm)

int adcResValue;  // variable to store the ADC reading
int adcResPin = A0;  // Pin the thermistor reading is connected to (HEX)

// temperature determination via Steinhard-Hall equation
float fitParamA = 0.002785219503;  // fit parameter a
float fitParamB = 0.000241846138;  // fit parameter b
float fitParamC = 0.000000831227;  // fit parameter c
float temperature;  // Calculated temperature
float KtoC = 273.15;   // how to tranform Kelvin to Celsius


void setup() {
  Serial.begin(9600);  // initialize serial monitor
}

void loop() {
  adcResValue = analogRead(adcResPin);  // read thermistor

  // careful in the next step: make sure the ADC value division
  // takes place as floats! otherwise you might get rounding issues.
  resTherm = resRef / (float(1023) / float(adcResValue) - 1);  // Equation 3.8

  // calculate temperature - equation (3.9)
  temperature = 1 / (
      fitParamA + fitParamB * log(resTherm) + fitParamC * pow(log(resTherm),3)
    ) - KtoC;

  Serial.print("Temperature (degC): ");
  Serial.println(temperature);

  delay(500);  // make it update a bit slower...
}
