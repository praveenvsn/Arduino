#include <Time.h>
  
  int led=4;

void setup() {
  
  setTime(8,00,00,2,10,2015);
  
  pinMode(led, OUTPUT);
  
  }

void loop() {
  
  if(second()%2==0)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
/*if (minute()==00&&second()==05||minute()==00&&second()==10||minute()==00&&second()==15||minute()==00&&second()==20)
  {
    for (int a=hour();a!=0;a--)
    {
      digitalWrite(led, HIGH);
      delay(250);
      digitalWrite(led, LOW);
      delay(250);
    }
    
    for (int b=minute()/15;b>0;b--)
    {
      digitalWrite(led, HIGH);
      delay(250);
      digitalWrite(led, LOW);
      delay(250);
    }
     
  }*/
  
}
