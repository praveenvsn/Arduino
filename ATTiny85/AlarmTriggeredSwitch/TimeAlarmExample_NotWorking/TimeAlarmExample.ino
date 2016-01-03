/*
 * TimeAlarmExample.pde
 *
 * This example calls alarm functions at 8:30 am and at 5:45 pm (17:45)
 * and simulates turning lights on at night and off in the morning
 * A weekly timer is set for Saturdays at 8:30:30
 *
 * A timer is called every 15 seconds
 * Another timer is called once only after 10 seconds
 *
 * At startup the time is set to Jan 1 2011  8:29 am
 */
 
#include <Time.h>
#include <TimeAlarms.h>

int LED = 4;
void setup()
{
  setTime(20,59,55,10,2,15); // set time to Saturday 8:29:00am Jan 1 2011
  // create the alarms 
  Alarm.alarmRepeat(6,0,0, MorningOnAlarm);  // 6:00am every day
  Alarm.alarmRepeat(9,0,0, MorningOffAlarm);  // 9:00am every day
  Alarm.alarmRepeat(21,0,0,EveningOnAlarm);  // 5:45pm every day 
  Alarm.alarmRepeat(21,0,5,EveningOffAlarm);  // 5:45pm every day 
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 

 
  //Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds    
  //Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds 
}

void  loop(){  
  //digitalClockDisplay();
  //Alarm.delay(1000); // wait one second between clock display
}

// functions to be called when an alarm triggers:
void MorningOnAlarm(){
  //Serial.println("Alarm: - turn lights off");    
  digitalWrite(LED, HIGH);
}

void MorningOffAlarm(){
  //Serial.println("Alarm: - turn lights off");    
  digitalWrite(LED, LOW);
}

void EveningOnAlarm(){
  //Serial.println("Alarm: - turn lights on");     
  digitalWrite(LED, HIGH);      
}

void EveningOffAlarm(){
  //Serial.println("Alarm: - turn lights on");
  digitalWrite(LED, LOW);     
}

void WeeklyAlarm(){
  //Serial.println("Alarm: - its Monday Morning");      
}

void ExplicitAlarm(){
  //Serial.println("Alarm: - this triggers only at the given date and time");       
}

void Repeats(){
  //Serial.println("15 second timer");         
}

void OnceOnly(){
  //Serial.println("This timer only triggers once");  
}

void digitalClockDisplay()
{
  // digital clock display of the time
  //Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  //Serial.println(); 
}

void printDigits(int digits)
{
  //Serial.print(":");
  //if(digits < 10)
    //Serial.print('0');
  //Serial.print(digits);
}

