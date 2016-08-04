/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground
 
For more information see http://learn.adafruit.com/photocells */

#include <Servo.h>
 
int photocellPin = 14;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the analog resistor divider
Servo face;
int facepin = 9;

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);  
  pinMode(13, OUTPUT); 
  face.attach(facepin);
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin);  
 
  Serial.print("Analog reading = ");
  Serial.print(photocellReading);     // the raw analog reading

  if (photocellReading > 600) {
    digitalWrite(13, HIGH); 
    face.write(180);
  } else {
    digitalWrite(13, LOW);
    face.write(0);
  }
  
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 10) {
    Serial.println(" - Dark");
  } else if (photocellReading < 200) {
    Serial.println(" - Dim");
  } else if (photocellReading < 500) {
    Serial.println(" - Light");
  } else if (photocellReading < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  delay(1000);
}
