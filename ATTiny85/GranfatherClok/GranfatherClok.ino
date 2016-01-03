#include <Time.h>
  
  int butt;

void setup() {
  
  setTime(8,59,10,14,10,2013);
  
  pinMode(0, OUTPUT);
  pinMode(4, INPUT);
  
  }

void loop() {
  
butt = digitalRead(4);

if (minute()==15&&second()==00||minute()==30&&second()==00||minute()==45&&second()==00||minute()==00&&second()==00||butt==HIGH)
  {
    for (int a=hour();a!=0;a--)
    {
      digitalWrite(0, HIGH);
      delay(250);
      digitalWrite(0, LOW);
      delay(250);
    }
    
    for (int b=minute()/15;b>0;b--)
    {
      digitalWrite(0, HIGH);
      delay(250);
      digitalWrite(0, LOW);
      delay(250);
    }
     
  }
  
}
