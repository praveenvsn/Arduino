#include <TimerOne.h>

// This example uses the timer interrupt to blink an LED
// and also demonstrates the use of a small scheduler to 
// do 2 actions at a time without using delay(). It 
// demonstrates the concept of multi-threading in Arduino. 
// For this approach, each functions should be desiged as 
// a state-machine which works on a particular state.

// Define the number of functions that are going to be invoked
#define MAX_ACTIONS 2

// Define a type for function pointer - delegate
typedef void(*Delegate)(void);

// Different states for blinking LED
enum blinkState{
  BLINKWAIT = 0,
  BLINK = 1
};

// Different states for printing messages to Serial Port
enum printState{
  PRINTWAIT = 0,
  PRINT = 1
};

// Declare variables for Blink state and Print state
enum blinkState blnkState = BLINKWAIT;
enum printState prntState = PRINTWAIT;

const int led = LED_BUILTIN;  // the pin with a LED

// Declare shared variables as volatile. This is very important
volatile bool tick = false;

// The interrupt will blink the LED
int ledState = LOW;

// Declare all the functions here
void blinkLED(void);
void printMessage(void);
void timer_tick(void);

//Declare an array of function pointer which holds the function address
Delegate action_delegate[MAX_ACTIONS] = {blinkLED, printMessage};

void setup(void)
{
  pinMode(led, OUTPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(timer_tick); // blinkLED to run every 0.15 seconds
  Serial.begin(115200);
}

// Checks the state, waits till timer is ticked and changes the state to blink the LED and print the message
void blinkLED(void)
{
  bool isTicked = false;
  switch(blnkState)
  {
    case BLINKWAIT:
      noInterrupts();
      isTicked = tick;
      tick = false;
      interrupts();
      if(isTicked)
      {
        blnkState = BLINK;
      }
    break;
    case BLINK:
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(led, ledState);
      prntState = PRINT;
      blnkState = BLINKWAIT;
    break;
    default:
    break;
  }
}

// Checks the state, waits till timer is ticked and then prints the message to Serial Port.
void printMessage(void)
{
  switch(prntState)
  {
    case PRINTWAIT:
    break;
    case PRINT:
      Serial.println("Hello");
      prntState = PRINTWAIT;
    break;
    default:
    break;
  }
}

void timer_tick(void)
{
  tick = true;
}

// The main program will blink the LED at set intervals and also prints a message without using delay() function
// to the Arduino Serial Monitor
void loop(void)
{
  // Scheduler which cycles through the function array and invokes each function in the array
  for(int i=0; i<MAX_ACTIONS; i++)
  {
    if((*action_delegate[i]) != NULL)  // Check if a function exists at the i'th location
      (*action_delegate[i])();         // and invoke it if exists
  }
}
