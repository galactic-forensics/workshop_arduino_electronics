/*
   LED on when button is pressed, otherwise off
*/

// Pin assignments
int ledPin = 2;   // pin for red LED
int buttonPin = 3;   // pin for button

// Variables
int buttonState = 0;  // button not pressed

void setup() {
  // declare pins
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read button state
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH)  // button pressed
  {
    digitalWrite(ledPin, HIGH);  // turn LED on
  }
  else  // button not pressed
  {
    digitalWrite(ledPin, LOW);  // turn LED off
  }
}
