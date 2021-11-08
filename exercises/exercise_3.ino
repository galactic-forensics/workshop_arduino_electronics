/*
  Fade

  This example shows how to fade an LED on pin 3 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.
*/

int led = 3;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

int fadeDelayTime = 30;// delay time for fade in ms
int stopDelayTime = 1000;   // delay time at top and bottom (ms)

int maxSteps = 255 / fadeAmount;   // integer division drops anything after decimal
int iter;  // iterator for for loop

// the setup routine runs once when you press reset:
void setup() {
  // declare led pin to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() { 
  // write the for loop in order to do the whole ramp
  for (iter = 0; iter < maxSteps; iter++){

    // calculate new brightness
    brightness = brightness + fadeAmount;

    // write the brighness to the set led pin
    analogWrite(led, brightness);

    // wait for the fade delay time set above
    delay(fadeDelayTime);
  }
  
  fadeAmount *= -1;
  
  // wait for stop delay time
  delay(stopDelayTime);
}
