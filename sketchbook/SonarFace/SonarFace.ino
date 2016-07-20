/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo sonarServo;  // create a utility object form the servo library to make controlling a servo easy
Servo faceServo;   // ditto

int pingSimPin = 2;
int pingState = 0;

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int count_dir = 1;
int incr_up = 1;
int incr_down = -1;
int top = 180;
int bottom = 0;
int pos = 0;

void setup() {
  sonarServo.attach(9);  // attaches the servo on pin 3 to the servo object
  faceServo.attach(10);  // attaches the servo on pin 3 to the servo object
  pinMode(pingSimPin,INPUT_PULLUP);
  Serial.begin(9600);
  
}


void loop() {
  while(true) {
    for (pos = init_pos(); limit_hit(pos); pos += incr()) { // goes from 0 degrees to 180 degrees and back
      // in steps of 1 degree
      sonarServo.write(pos);              // tell servo to go to position in variable 'pos'
      pingState = digitalRead(pingSimPin);
      if (pingState == LOW) {
        faceServo.write(pos);
        Serial.println(pos);
      }

      delay(15);                       // waits 15ms for the servo to reach the position
    }
    // reverse direction of count
    count_dir = !count_dir;
  }
}


/*
 * Utilities to make a loop that runs forward and then backwards 
 *    It means the starting point varies and the end points vary and 
 *    the increment value sign needs to change.
 */
int init_pos() {
  return (count_dir ? bottom : top);
}

int limit_hit(int pos) {
  if (count_dir) {
    return (pos <= top);
  } 
  return (pos >= bottom);
}

int incr() {
  if (count_dir) {
    return (incr_up);
  }
  return (incr_down);
}
/* 
 *  end of utilities for incrementing
 */


