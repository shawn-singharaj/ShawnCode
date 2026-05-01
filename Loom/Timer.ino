// Timer with circuit playground

#include <AsyncDelay.h>

int buttonPin = 4;
int buttonPin2 = 5;
int switchPin = 7;

AsyncDelay delay_1s; // will output every 1 second

volatile int count = 0; // initialize count to 0

volatile int buttonFlag;
volatile int switchFlag;
volatile bool switchState;
volatile bool isPaused = false; // track pause state


void setup(void)
{
  pinMode(buttonPin, INPUT_PULLDOWN); // initialize button
  pinMode(buttonPin2, INPUT_PULLDOWN); // initialize button
  pinMode(switchPin, INPUT_PULLUP); // initialize switch
  Serial.begin(9600);
  while(!Serial); // Pause program till serial opens
  Serial.println("Starting timer:");
  // Start counting
  delay_1s.start(1000, AsyncDelay::MILLIS); 
  attachInterrupt(digitalPinToInterrupt(buttonPin), reset_Timer, RISING); // interrupt if button pressed
  attachInterrupt(digitalPinToInterrupt(buttonPin2), reset_Timer, RISING);  
  attachInterrupt(digitalPinToInterrupt(switchPin), pause_Timer, CHANGE); // interrupt if switch flipped
}

void loop(void)
{
  if(buttonFlag)
  {
    count = 0; // reset count
    Serial.println(count);
    delay_1s.start(1000, AsyncDelay::MILLIS); // restart timer
    buttonFlag = 0; // exit 
  }

  if(switchFlag)
  {
    delay(20);
     // read switch state
    isPaused = switchState; // HIGH = pause, LOW = resume (INPUT_PULLUP logic)

    if (isPaused)
    {
      Serial.println("Paused");
    }
    else
    {
      Serial.println("Resumed");
      delay_1s.start(1000, AsyncDelay::MILLIS); // clean restart of timer on resume
    }

    switchFlag = 0;
    }
 
//   if (switchFlag)
// {
//   delay(20); // debounce
//   switchState = digitalRead(switchPin); // update switch state
//   switchFlag = 0;
// }

  // after the timer starts counting and is expired, enter loop
  if (!isPaused && delay_1s.isExpired())
 {
    Serial.println(++count); // output that the timer is up
    delay_1s.repeat(); // count from when the delay expired, not now
  }
}

void reset_Timer()
{
  buttonFlag = 1;
}

void pause_Timer()
{
  switchFlag = 1;
}
  /*else // if switch flipped back, resumt count
  {
    Serial.println("Resumed");
    delay_1s.start(1000, AsyncDelay::MILLIS); // Resume the timer
    switchFlag = 0;
  }*/
  