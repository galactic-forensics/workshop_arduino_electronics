/*
  Exercise 1: blink an externally connected LED
*/

int ledPin = 2;  // pin the LED is connected to

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);  // set up pin as output
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin, HIGH);  // turn on LED
  delay(3000);  // wait 3 seconds
  digitalWrite(ledPin, LOW);  // turn LED off
  delay(1000);  // wait for a second
}
