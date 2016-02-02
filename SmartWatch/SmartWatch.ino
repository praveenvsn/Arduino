/*

  Bitmap.pde
  
  Show simple bitmap

  >>> Before compiling: Please remove comment from the constructor of the 
  >>> connected graphics display (see below).

  Universal 8bit Graphics Library, https://github.com/olikraus/u8glib/
  
  Copyright (c) 2011, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
  
*/


#include "U8glib.h"
#include <Time.h>
#include <TimeAlarms.h>
#include <SoftwareSerial.h>

//#define DEBUG // uncomment this to print debug messages

char c = ' ';
char* timeVal = "Sync";
char* dateVal = "-----";
char* secVal = "..";
int sec = 0;
const int BTStatePin = 5;
int durationCounter = 0; 
String btStatusText = "Disconnected";
unsigned long duration;
bool isConnected = false;
const int btConnectivityPollTime = 3; // in seconds

SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

// setup u8g object, please remove comment from one of the following constructor calls
// IMPORTANT NOTE: The following list is incomplete. The complete list of supported 
// devices with all constructor calls is here: https://github.com/olikraus/u8glib/wiki/device
U8GLIB_SSD1306_128X64 u8g(13, 11, 10, 9, 8);  // SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset=8

/*
  1. Always 1 byte
  2. Store Lower byte first
*/
const int envBitmapWidth = 16;
const int envBitmapHeight = 12;
const uint8_t envelope_bitmap[] PROGMEM = {
  0xff,0xff,
  0x03,0xc0,
  0x05,0xa0,
  0x09,0x90,
  0x11,0x88,
  0xe1,0x87,
  0x01,0x80,
  0x01,0x80,
  0x01,0x80,
  0x01,0x80,
  0x01,0x80,
  0xff,0xff
};

const int btBitmapWidth = 8;
const int btBitmapHeight = 12;
const uint8_t bluetooth_connected_bitmap[] PROGMEM = {
  0x08,
  0x18,
  0x28,
  0x4a,
  0x2c,
  0x18,
  0x18,
  0x2c,
  0x4a,
  0x28,
  0x18,
  0x08
};
const uint8_t bluetooth_disconnected_bitmap[] PROGMEM = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

const int cellBitmapWidth = 8;
const int cellBitmapHeight = 12;
const uint8_t cell_signal_full_bitmap[] PROGMEM = {
  0x80,
  0x80,
  0x80,
  0x80,
  0xa0,
  0xa0,
  0xa0,
  0xa0,
  0xa8,
  0xa8,
  0xa8,
  0xa8
};

void draw(void) {
  
  // graphic commands to redraw the complete screen should be placed here  
  u8g.drawXBMP( 0, 0, envBitmapWidth, envBitmapHeight, envelope_bitmap);
  
  if(!isConnected)
  {
    u8g.drawXBMP(20, 0, btBitmapWidth, btBitmapHeight, bluetooth_disconnected_bitmap);
    dateVal = "-----";
    timeVal = "Sync..";
    //secVal = "..";
  }
  else
    u8g.drawXBMP(20, 0, btBitmapWidth, btBitmapHeight, bluetooth_connected_bitmap);

  u8g.drawXBMP( 32, 0, cellBitmapWidth, cellBitmapHeight, cell_signal_full_bitmap);
  // Write Date String
  u8g.setFont(u8g_font_courB08);
  u8g_uint_t dateWidth = u8g.getStrWidth(dateVal);
  u8g_uint_t dateX = (u8g.getWidth()-dateWidth);
  u8g.setFontPosTop();
  u8g.drawStr(dateX, 0, dateVal);
  
  // Write Time String
  u8g.setFont(u8g_font_profont29);
  u8g_uint_t textWidth = u8g.getStrWidth(timeVal);
  u8g_uint_t textHeight = u8g.getFontAscent()-u8g.getFontDescent();
  u8g_uint_t x = (u8g.getWidth()/2)-(textWidth/2);
  u8g_uint_t y = (u8g.getHeight()/2)-(textHeight/2);
  u8g.setFontPosTop();
  u8g.drawStr(x, y, timeVal);

  // Write Sec string which is very small compared to time string
  /*
  u8g.setFont(u8g_font_profont17);
  u8g_uint_t secWidth = u8g.getStrWidth(secVal);
  u8g_uint_t secHeight = u8g.getFontAscent()-u8g.getFontDescent();
  u8g_uint_t xSec = x + textWidth + 5;
  u8g_uint_t ySec = (u8g.getHeight()/2)-(secHeight/2);
  u8g.setFontPosBottom();
  u8g.drawStr(xSec, ySec, secVal);
  */
}


void setup(void) {
  //u8g.setRot180();
  pinMode(BTStatePin, INPUT);
  Serial.begin(9600);
  setTime(00,00,0,1,1,1970);  // Initialize the timer to a value so that Alarm functions work properly.
  Alarm.timerRepeat(btConnectivityPollTime, BTConnected);  // Check bluetooth connectivity every 2 second(s). Refine the time if required.
  Alarm.timerRepeat(1, secs_tick);
  #ifdef DEBUG
  Serial.println(year());
  #endif
  // HC-05 default serial speed for commincation mode is 9600
  BTserial.begin(9600);  
  ClearDisplay();
}

void loop(void) {
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTserial.available())
  {  
      //c = BTserial.read();
      #ifdef DEBUG
      Serial.println(BTserial.readString());
      #endif
      processSyncMessageBluetooth();
  }
  if(Serial.available() ) 
   {
     processSyncMessage();
   }
   if(timeStatus() == timeNotSet) 
   {
     Serial.println("waiting for sync message");
     u8g.firstPage();  
      do {
        draw();
      } while( u8g.nextPage() ); 
   }
   else
   {
     getDateTime();
     // picture loop
      u8g.firstPage();  
      do {
        draw();
      } while( u8g.nextPage() );  
   }
  Alarm.delay(0.4);
}

void getDateTime(){
    if(year() == 1970)
      return;
    String currentTime = "";
    String currentDate = "";
    String currentSecs = "";
    currentDate.concat(get2DigitEquivalent(day()));
    currentDate.concat("/");
    currentDate.concat(get2DigitEquivalent(month()));
    currentDate.toCharArray(dateVal, currentDate.length()+1);    
    currentTime.concat(get2DigitEquivalent(hour()));
  /*  if(sec%2==0)
      currentTime.concat(" ");
    else
      currentTime.concat(":"); 
  */
    currentTime.concat(":"); 
    currentTime.concat(get2DigitEquivalent(minute()));
    currentTime.toCharArray(timeVal, currentTime.length()+1);
    //currentSecs.concat(get2DigitEquivalent(second()));
    //currentSecs.toCharArray(secVal, currentSecs.length()+1);
    #ifdef DEBUG
    Serial.print(currentDate);
    Serial.print(" ");
    Serial.print(currentTime);
    Serial.print(":");
    Serial.print(currentSecs);
    #endif
}

void printDigits(int digits){
   // utility function for digital clock display: prints preceding colon and leading 0
   Serial.print(":");
   if(digits < 10)
     Serial.print('0');
   Serial.print(digits);
}

void processSyncMessage() {
   // if time sync available from serial port, update time and return true
   while(Serial.available() >=  TIME_MSG_LEN ){  // time message consists of header & 10 ASCII digits
     char c = Serial.read() ; 
     Serial.print(c);  
     if( c == TIME_HEADER ) {       
       time_t pctime = 0;
       for(int i=0; i < TIME_MSG_LEN -1; i++){   
         c = Serial.read();      
         Serial.print(c);    
         if( c >= '0' && c <= '9'){   
           pctime = (10 * pctime) + (c - '0') ; // convert digits to a number    
         }
       }   
       setTime(pctime);   // Sync Arduino clock to the time received on the serial port
     }  
   }
}

void processSyncMessageBluetooth() {
   // if time sync available from serial port, update time and return true
   while(BTserial.available() >=  TIME_MSG_LEN ){  // time message consists of header & 10 ASCII digits
     char c = BTserial.read() ; 
     Serial.print(c);  
     if( c == TIME_HEADER ) {       
       time_t pctime = 0;
       for(int i=0; i < TIME_MSG_LEN -1; i++){   
         c = BTserial.read();      
         Serial.print(c);    
         if( c >= '0' && c <= '9'){   
           pctime = (10 * pctime) + (c - '0') ; // convert digits to a number    
         }
       }   
       setTime(pctime);   // Sync Arduino clock to the time received on the serial port
     }  
   }
}

String get2DigitEquivalent(int digits){
   String twoDigitEqt = "";
   if(digits < 10)
     twoDigitEqt = "0";
   String dgt = "";
   dgt.concat(twoDigitEqt);
   dgt.concat(digits);
   return dgt;
}


void ClearDisplay()
{
  digitalWrite(8, LOW);
  delay(10);
  digitalWrite(8, HIGH);
}


void BTConnected()
{
  duration = pulseIn(BTStatePin, LOW, 1500000);
  if(duration == 0)
    durationCounter = durationCounter+1;
  //Serial.println(duration);
  isConnected = durationCounter > 0 ? true:false;
  durationCounter = 0;
  #ifdef DEBUG
  if(isConnected)
    btStatusText = "Connected";
  else
    btStatusText = "Disconnected";
  Serial.println(btStatusText);
  #endif
}

void secs_tick()
{
  if(sec == 59)
    sec = 0;
  else
    sec += 1;  
//  BTConnected();
}


