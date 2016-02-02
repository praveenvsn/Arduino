/*
 Mood Lighting

 This example shows how to fade an LED using the analogWrite() function.

 The circuit:
 * LED attached from digital pin 9 to ground.

 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe

 http://www.arduino.cc/en/Tutorial/Fading

 This example code is in the public domain.

 */

int motorPin = 9;    // Vibration motor connected to digital pin 9
float tOn;
void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  // nothing happens in setup
}

void loop() {
  /*for (float x=0;x<PI;x=x+0.00001){
     tOn=255*abs(sin(x*(180/PI)));           // calculate the brightness for the red led
     Serial.print("PWM:");
     Serial.println(tOn);
     analogWrite(motorPin,tOn);
     delay(1000);
   }
   */
   digitalWrite(motorPin,1);
   delay(2000);
   digitalWrite(motorPin,0);
   delay(1);
}


