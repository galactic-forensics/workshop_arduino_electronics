# Answers to questions

Here are answers to all questions that were asked in the 
[notes](https://raw.githubusercontent.com/galactic-forensics/workshop_arduino_electronics/main/notes_arduino_intro/main_arduino_intro.pdf).

## Question 0

Dividing two integers in C++ results in an integer as a result. This integer is always rounded down, i.e.,
```cpp
int a = 8;
int b = 3;
int c = a/b;
```
results in `c` being equal to 2. If you are interested in determining the remainder of the division, you could store it in variable `d` as following:
```cpp
int d = a%b;  // calculate reminder
```

In order to round, we need to include the math library. To do so, put the following statement at the top of your file:
```cpp
#include<math.h>
```
This gives you many math functions, an overview can be found [here](https://www.nongnu.org/avr-libc/user-manual/group__avr__math.html).
The following code can then be used to round appropriately:
```cpp
int a = 8;
int b = 3;
int c = round(float(a) / float(b));
```

A boolean variable takes two states, `true` or `false`. These are also often expressed as the integers `1` and `0`, respectively. Inside an `if` statement, it could be used as following:
```cpp
bool checker = true;
if (checker) {
    // do stuff when the checker is true
}
else {
    // do stuff when the checker is false
}
```
Note the following peculiarity:
```cpp
int a = 3;
int b = 2;
int c = 0;
```
If you simply run `if (a)` or `if (b)` here, it would return `true`, however `if (c)` would be false (since it is zero). Any integer except for zero is `true`. However, `if (a == b)` would be false, since an integer comparison takes place and that comparison returns false. The comparisons `if (a == true)` would also be `false`, since `a` is an integer and not a boolean value.

If you have a boolean variable assigned and want to switch its state later, you could do, e.g., the following:
```cpp
bool a = true;
// do some stuff while a is true
// ...
// now switch the state to the opposite
a = !a;
```

## Question 1

The temperature range is around 1000 degrees. A 10bit ADC only has 1024 states to work with, therefore each ADC state would change the temperature by roughly one degree. To improve the precision, we would need an ADC with a higher resolution or a thermocouple with a lower range.


## Question 2

The Steinhard-Hall equation seems to do a great job in fitting the temperature table. So we can simply fit this equation to the lookup table and use these parameters. A solution to this can be found in [this python script](../figures/03_temperature/thermistor.py).

## Question 3

Between 25 and -20 degrees Celsius, the resistance of the thermistor changes between 87.43kOhm and 10kOhm.
Equation (3.8) of the notes tells us how we can calculate the thermal resistance using our reference resistor. 

We can now calculate the bit values that the ADC would measure at 24 and 25 degrees Celsius. These values are 523 and 512, respectively, therefore we get a difference of 11 bits per degree, or around 0.1 degree per bit.

At the cool end of the temperature scale, we get bit values of 913 and 918 for -19 and -20 degrees Celsius, respectively. This means that the minimum we can read is going to be 0.2 degrees Celsius per bit. 


## Question 4

Knowing that the Peltier cooler takes 5A at 12V, we can calculate its resistance to be 2.4Ohm. This means that at 5V, the cooler would still try to consume 2.1A. The maximum an Arduino pin can supply is 20mA. 

## Question 5

See diagram provided with the solution for [exercise 14](../exercises/exercise_14).
