// Plant growing sensor, detects capacitence, light level, and temperature.

#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay timer;
float tempF;
int lightValue;
int capValue;
const float tempThreshold = 90.0;
const int lightThreshold = 500;
const int capThreshold = 575;
volatile int switchFlag;
int i;

int song[12][2] = {
    {64, 100},  // song[0][0]], song[0][1]]
    {60, 100},  // song[1][0]], song[1][1]]
    {127, 200},
    {68, 100},  // song[2][0]], song[2][1]]
    {60, 100},  // song[3][0]], song[3][1]]
    {127, 200},
    {67, 100},  // song[4][0]], song[4][1]]
    {60, 100},  // song[5][0]], song[5][1]]
    {127, 200},
    {64, 100},
    {60, 100},
    {72, 200},
  };

void setup() 
{
  CircuitPlayground.begin();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(7), switchFlipped, CHANGE);
  while(!Serial);
  timer.start(2000, AsyncDelay::MILLIS);
}

void loop() 
{
  tempF = CircuitPlayground.temperatureF();
  lightValue = CircuitPlayground.lightSensor();
  capValue = CircuitPlayground.readCap(6);

  int green = map(capValue, 575, 1018, 0, 255);

  if(capValue > capThreshold)
  {
    for(i = 0; i < 10; i++)
    {
      if(tempF >= tempThreshold)
      {
        break;
      }
      CircuitPlayground.setPixelColor(i, 0, green, 0);
      delay(20);
    }
  }

  if(capValue <= capThreshold)
  {
    blueTwo();
  }

  if(tempF >= tempThreshold)
  {
    Serial.print("Temperature: ");
    Serial.println(tempF);
    for(i=0; i<10; i++)
    {
      int rand = random(0, 10);
      int rand2 = random(0, 10);
      if(rand2 == rand)
      {
        while(rand2 == rand)
        {
          rand2 = random(0, 10);
        }
      }
      CircuitPlayground.setPixelColor(rand, 255, 0, 0);
      CircuitPlayground.setPixelColor(rand2, 255, 0, 0);
      delay(100);
      CircuitPlayground.clearPixels();
    }
  }
 
  if(lightValue < lightThreshold)
  {
    if(switchFlag == 1)
    {
      for(i = 0; i < sizeof(song) / sizeof(song[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
      {
        CircuitPlayground.playTone(((440 / 32.0) * pow(2.0, ((song[i][0] - 9.0) / 12.0))), song[i][1]);
        //Serial.println(midi[song[i][0]]);
        delay(1);
      }      
    }

    else
    {
      Serial.print("Nighttime mode: ");
      Serial.println(lightValue);
      delay(1000);
    }
 
  }
  
  if(timer.isExpired())
  {
    Serial.print("Capacitence: ");
    Serial.println(capValue);
    timer.repeat();
  }
}


void blueTwo()
{
  int rand = random(0, 10);
  int rand2 = random(0, 10);
  int randBlue = random(0, 256);
  CircuitPlayground.setPixelColor(rand, 0, 0, randBlue);
  CircuitPlayground.setPixelColor(rand2, 0, 0, randBlue);

  delay(200);

  int ii = 9;
  
  for(int i = 0; i <= ii; i++)
  {
    if(i != rand && i != rand2)
    {
      CircuitPlayground.setPixelColor(i, 0, 0, randBlue);
    }
    if(ii != rand && ii != rand2)
    {
      CircuitPlayground.setPixelColor(ii, 0, 0, randBlue);
       
    }
    ii--;
    delay(200);
  }
  CircuitPlayground.clearPixels();
}

void switchFlipped()
{
  if(switchFlag == 1)
  {
    switchFlag = 0;
  }
  else
  {
    switchFlag = 1;
  }
}