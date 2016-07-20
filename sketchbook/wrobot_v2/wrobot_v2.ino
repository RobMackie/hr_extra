#include <Servo.h>

#define RIGHT_WHEEL_PIN 10
#define LEFT_WHEEL_PIN 11

#define SENSOR_PIN  0

Servo leftMotor;
Servo rightMotor;

enum motors_t {
    LEFT_MOTOR,
    RIGHT_MOTOR,
    LAST_MOTOR
};

Servo *motors[LAST_MOTOR];

#define FULL_SPEED 90

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    motors[LEFT_MOTOR] = &leftMotor;
    motors[RIGHT_MOTOR] = &rightMotor;

    leftMotor.attach(LEFT_WHEEL_PIN);
    rightMotor.attach(RIGHT_WHEEL_PIN);
    moveMotor(LEFT_MOTOR, 0);
    moveMotor(RIGHT_MOTOR, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  // 0 means one direction, 180 means the other and 90 means stay still
    int value = analogRead(SENSOR_PIN);
    value = map(value, 0, 1023, 0, 100);
    Serial.println(value);

    if (value >= 50) {
         moveMotor(LEFT_MOTOR, 0);
         moveMotor(RIGHT_MOTOR, FULL_SPEED/2);
    } else {
         moveMotor(LEFT_MOTOR, FULL_SPEED/2);
         moveMotor(RIGHT_MOTOR,0);
    }
    
    delay(2);
}

/*
 * moveMotor
 *     motor : LEFT_MOTOR | RIGHT_MOTOR
 *     motorSpeed [-90, 90] negative means backwards, positive means full, 0 means still)
 */
void moveMotor(int motor, int motor_speed) {
      
      if (motor == RIGHT_MOTOR) {
           motor_speed *= -1;     
      }

      int servo_in = motor_speed + 90;
      
      if (servo_in < 0) { 
          servo_in = 0;
      } else if (servo_in > 180) {
          servo_in = 180;
      }
      motors[motor]->write(servo_in);      
}

