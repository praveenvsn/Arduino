#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <Time.h>
#include <TimeAlarms.h>

const int PIR_PIN = 4; //PB4 (Pin 3)
const int SWITCH_PIN = 3; //PB3 (Pin 2)

volatile bool trigger = HIGH;

void sleep() {

	GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
	PCMSK |= _BV(PCINT4);                   // Use PB4 as interrupt pin
	ADCSRA &= ~_BV(ADEN);                   // ADC off
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement
	sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
	sei();                                  // Enable interrupts
	sleep_cpu();                            // sleep
	cli();                                  // Disable interrupts
	PCMSK &= ~_BV(PCINT4);                  // Turn off PB3 as interrupt pin
	sleep_disable();                        // Clear SE bit
	ADCSRA |= _BV(ADEN);                    // ADC on
	sei();                                  // Enable interrupts
} // sleep


void setup() {
	// put your setup code here, to run once:
	pinMode(PIR_PIN, INPUT);
	pinMode(SWITCH_PIN, OUTPUT);
	SetSwitch(LOW);
	setTime(20, 06, 0, 17, 2, 16); // set time to Saturday 8:29:00am Jan 1 2011
								   // create the alarms 
	Alarm.alarmRepeat(6, 15, 0, MorningAlarm);  // 8:30am every day
	Alarm.alarmRepeat(18, 15, 0, EveningAlarm);  // 5:45pm every day 

}

ISR(PCINT0_vect)
{

}


void MorningAlarm() {
	trigger = LOW;
}

void EveningAlarm() {
	trigger = HIGH;
}

void SetSwitch(bool status)
{
	digitalWrite(SWITCH_PIN, status);
}

void loop() {
	// put your main code here, to run repeatedly:
	sleep();
	if (trigger)
		SetSwitch(digitalRead(PIR_PIN));
	else
		SetSwitch(LOW);
}