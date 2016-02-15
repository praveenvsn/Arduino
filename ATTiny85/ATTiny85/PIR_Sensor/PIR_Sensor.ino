
#include <Time.h>
#include <TimeAlarms.h>

const int PIR_PIN = 4; //PB4 (Pin 3)
const int LED_PIN = 3; //PB3 (Pin 2)
const int PIR_EN=0; //PB0 (Pin 5)

volatile bool trigger = HIGH;

void setup() {
	// put your setup code here, to run once:
	pinMode(PIR_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	//pinMode(PIR_EN, OUTPUT);
	//Enable PIR
	//SetPIR(HIGH);
	//delay(1000);  // Required for PIR to initialize  
	setTime(22, 33, 0, 11, 2, 16); // set time to Saturday 8:29:00am Jan 1 2011
								  // create the alarms 
	Alarm.alarmRepeat(6, 15, 0, MorningAlarm);  // 8:30am every day
	Alarm.alarmRepeat(18, 15, 0, EveningAlarm);  // 5:45pm every day 

}

void MorningAlarm() {
	// digitalWrite(LED_PIN, LOW);    
	trigger = LOW;
	//SetPIR(LOW);
}

void EveningAlarm() {
	//digitalWrite(LED_PIN, HIGH);           
	trigger = HIGH;
	//SetPIR(HIGH);
}

void SetPIR(bool status)
{
	digitalWrite(PIR_EN, status);
}
void SetLED(bool status)
{
	digitalWrite(LED_PIN, status);
}
void loop() {
	// put your main code here, to run repeatedly:
	if (trigger)
		SetLED(digitalRead(PIR_PIN));
	else
		SetLED(LOW);
	Alarm.delay(10);
}