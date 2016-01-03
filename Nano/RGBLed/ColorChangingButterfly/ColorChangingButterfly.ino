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
float RGB[3] = {255,255,0}; //Generates Gold color
int greenLed = 9;    // LED connected to digital pin 9
int blueLed = 10;
int redLed = 11;

void setup() {
  analogWrite(redLed,RGB[0]);
   analogWrite(greenLed,RGB[1]);
   analogWrite(blueLed,RGB[2]);
}

void loop() {
   
}


