/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include <NewPing.h>

Servo sonarServo;  // create a utility object form the servo library to make controlling a servo easy
Servo faceServo;   // ditto

int pingSimPin = 2;
int pingState = 0;

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int count_dir = 1;
int incr_up = 4;
int incr_down = -4;
int top = 180;
int bottom = 0;
int pos = 0;

#define NEAR 10
#define FAR 60

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int distance;

int count = 0;
#define SIZE 5
int sample[SIZE];

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
      delay(10);
      distance = sonar.ping_cm();
      delay(10);     
      count++;
      sample[count%SIZE] = distance;
      if (test_hit()) {
        Serial.print(count); Serial.print(" : ");
        Serial.print("Ping: ");
        Serial.print(distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
        Serial.println("cm");
        faceServo.write(180 - pos);
      }

      delay(30);                       // waits 15ms for the servo to reach the position
    }
    // reverse direction of count
    count_dir = !count_dir;
  }
}

int test_hit() 
{
    int sum = 0;
    for (int ii = 0; ii < SIZE; ii++) {
       if ( NEAR < sample[ii] && sample[ii] < FAR) {
         sum++;
       }
    }
    if (sum > 2) {
       return (1);
    }
    return (0);
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


