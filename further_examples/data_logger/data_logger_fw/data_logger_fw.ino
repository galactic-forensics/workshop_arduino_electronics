/*
 * Data logger firmware
 * 
 * Simple demo program to show the capabilities of the Arduino Serial interface.
 * When a ? is sent to the Arduino, it will respond with `23.5`, which could,
 * e.g., be a temperature reading of a sensor.
 * Sending any other key does not trigger a response.
 * 
 * Furthermore, if a response is set, an LED will blink once in order to
 * indicate that the Arduino has read it.
 */


const int ledPin = 3;  // pin where our LED is connected

float result = 23.5;  // the result to send back

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  // initialize the serial interface. note the baud rate!
}

void blink_led() {
  // function to blink the LED for 100 ms
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}

void loop() {

  char inByte;  // where to store the read data
  
  if (Serial.available() > 0) {  // Check if Serial data
    inByte = Serial.read();  // Read what is coming in

    if (inByte == '?') {  // if a question mark was sent...
      Serial.println(result);  // return the result
      blink_led();  // blink the LED
    }
    
  }

}
