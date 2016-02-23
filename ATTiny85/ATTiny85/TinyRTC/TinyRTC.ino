/*
 Name:		TinyRTC.ino
 Created:	2/21/2016 8:32:03 PM
 Author:	Praveen
*/

/* ATtiny85 as an I2C Master   Ex3        BroHogan                         1/22/11
* I2C master reading DS1621 temperature sensor & DS1307 RTC. Display to I2C GPIO LED.
* SETUP:
* ATtiny Pin 1 = (RESET) N/U                      ATtiny Pin 2 = (D3) N/U
* ATtiny Pin 3 = (D4) to LED1                     ATtiny Pin 4 = GND
* ATtiny Pin 5 = SDA on all devices               ATtiny Pin 6 = (D1) to LED2
* ATtiny Pin 7 = SCK on all devices               ATtiny Pin 8 = VCC (2.7-5.5V)
* NOTE! - It's very important to use pullups on the SDA & SCL lines!
* DS1621 wired per data sheet. This ex assumes A0-A2 are set LOW for an addeess of 0x48
* DS1307 wired per data sheet. This ex assumes A0-A2 are set LOW for an addeess of 0x68
* PCA8574A GPIO was used wired per instructions in "info" folder in the LiquidCrystal_I2C lib.
* This ex assumes A0-A2 are set HIGH for an addeess of 0x3F
* LiquidCrystal_I2C lib was modified for ATtiny - on Playground with TinyWireM lib.
* TinyWireM USAGE & CREDITS: - see TinyWireM.h
*/

//#define DEBUG
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
#include <TinyRTClib.h>

#define DS1307_ADDR   0x68              // I2C real time clock
#define LED1_PIN         4              // ATtiny Pin 3

RTC_DS1307 rtc;                      // Set up real time clock object
uint8_t hourvalue;


void setup() {
	pinMode(LED1_PIN, OUTPUT);
	TinyWireM.begin();                    // initialize I2C lib
	rtc.begin();                  // Begin DS1307 real time clock
	if (!rtc.isrunning()) {      // Uncomment lines below first use of clock to set time
								 //Serial.println("RTC is NOT running!");
								 // following line sets the RTC to the date & time this sketch was compiled
#ifdef DEBUG
		Blink(LED1_PIN, 5);                    // show setting time  
#endif // DEBUG

		rtc.adjust(DateTime(__DATE__, __TIME__));
		delay(2000);
	}
}


void loop() {
	CheckTime();

}

void CheckTime()
{
	DateTime now = rtc.now();           // Get the RTC info
	hourvalue = now.hour();             // Get the hour

	if (hourvalue >= 19 && hourvalue <= 21)
		digitalWrite(LED1_PIN, HIGH);
	else
		digitalWrite(LED1_PIN, LOW);
}

//#ifdef DEBUG
void Blink(byte led, byte times) { // poor man's GUI
	for (byte i = 0; i< times; i++) {
		digitalWrite(led, HIGH);
		delay(400);
		digitalWrite(led, LOW);
		delay(175);
	}
}
//#endif
