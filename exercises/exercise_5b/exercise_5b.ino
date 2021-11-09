/*
  Blink with button
  
  When button is pressed, turn an LED on for 3 seconds.

  Note: This is the dumb routine in which you cannot 
  add time!
*/

// Pin assignments
int ledPin = 2;
int buttonPin = 3;

// Variables
int buttonState = 0;

void setup() {
  // declare pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void led_on() {
  digitalWrite(ledPin, HIGH);
  delay(3000);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // read the button state
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    led_on();  // toggle LED for 3 seconds
  }
}
