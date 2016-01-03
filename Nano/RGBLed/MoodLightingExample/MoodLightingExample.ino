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

float RGB[3];
int greenLed = 9;    // LED connected to digital pin 9
int blueLed = 10;
int redLed = 11;

int pin9Green = 215;
int pin10Blue = 0;
int pin11Red = 255;

void setup() {
  // nothing happens in setup
}

void loop() {
  for (float x=0;x<PI;x=x+0.00001){
     RGB[0]=255*abs(sin(x*(180/PI)));           // calculate the brightness for the red led
     RGB[1]=255*abs(sin((x+PI/3)*(180/PI)));    // calculate the brightness for the green led
     RGB[2]=255*abs(sin((x+(2*PI)/3)*(180/PI)));// calculate the brightness for the blue led
     //ambientLight=analogRead(ldrPin); // read an store the ambient light
     //if(ambientLight>600){ // start only if the ambient light is very low
       //  write the brightness on the leds
       analogWrite(redLed,RGB[0]);
       analogWrite(greenLed,RGB[1]);
       analogWrite(blueLed,RGB[2]);
     //}
     //else{
     //  digitalWrite(redLed,LOW);
     //  digitalWrite(greenLed,LOW);
     //  digitalWrite(blueLed,LOW);
     //}
     for(int i=0;i<3;i++){
       if(RGB[i]<1){
         delay(100);
       }
       if(RGB[i]<5){
         delay(50);
       }
       if(RGB[i]<10){
         delay(10);
       }
       if(RGB[i]<100){
         delay(5);
       }
     }
     delay(1);
   }
}


