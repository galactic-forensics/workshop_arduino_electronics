/*
  Blink with button
  
  When button is pressed, turn an LED on for 3 seconds.

  In this version you can add time by pressing the button again and again.
  Not that the `pressedTime` variable is set to `-onTime` such that LED
  is not on when the Arduino starts.
*/

// Pin assignments
int ledPin = 2;
int buttonPin = 3;

// Variables
int buttonState = 0;

int onTime = 3000;  // on time in milliseconds

long pressedTime = -onTime;  // time when button last pressed
long deltaTime;  // time delta, to be used later


void setup() {
  // declare pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void led_on() {
  pressedTime = millis();  // current run time in milliseconds
}

void loop() {
  // read the button state
  buttonState = digitalRead(buttonPin);

  // register button presses
  if (buttonState == HIGH) {
    led_on();
  }

  // get time since button pressed
  deltaTime = millis() - pressedTime;

  // control LED
  if (deltaTime > onTime) {
    digitalWrite(ledPin, LOW);  // LED off
  } else {
    digitalWrite(ledPin, HIGH);  // LED on
  }
}
