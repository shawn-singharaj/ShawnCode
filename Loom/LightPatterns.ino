// Manipulate the neopixel lights to display patterns.

#include <Adafruit_CircuitPlayground.h>

int i;
volatile int button4Flag;
volatile int button5Flag;
volatile int switchFlag;
int modeCounter = 1;

void setup() 
{

  CircuitPlayground.begin();

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(4), button4Pressed, RISING); // interrupt if button pressed
  attachInterrupt(digitalPinToInterrupt(5), button5Pressed, RISING);  
  attachInterrupt(digitalPinToInterrupt(7), switchFlipped, CHANGE);
}

void loop()
{
   
    if(switchFlag)
    {
      switch(modeCounter)
      {
        case 1:   
        loadingCycle();
        Serial.println("Loading Cycle");
        break;
        
        case 2:
        sparkleWhite();
        Serial.println("White Sparkle");
        break;

        case 3:
        rainbowCycle(100, 10); 
        Serial.println("Rainbow Cycle");
        break;

        case 4:
        sparkleRainbow();
        Serial.println("Rainbow Sparkle");
        break;

        case 5: 
        plusTwo();
        Serial.println("Plus Two");
        break;
      }
    }

    if(switchFlag == 0)
    {
      CircuitPlayground.clearPixels();
    }
    

    if(button4Flag)
    {
      modeCounter++;
      
      if(modeCounter == 6)
      {
        modeCounter = 1;
      }
      //Serial.println(modeCounter);
      button4Flag = 0;
    } 

    if(button5Flag)
    {
      modeCounter--;
      
      if(modeCounter == 0)
      {
        modeCounter = 5;
      }
      //Serial.println(modeCounter);
      button5Flag = 0;
    }
}

void rainbowCycle(int currentSpeed, int stripLen) {

  // Make an offset based on the current millisecond count scaled by the current speed.
  uint32_t offset = millis() / currentSpeed;

  // Loop through each pixel and set it to an incremental color wheel value.
  for(i=0; i<10; ++i) 
  {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));
  }
}

void sparkleWhite()
{
  for(i=0; i<10; i++)
  {
    int rand = random(0, 10);
    CircuitPlayground.setPixelColor(rand, 255, 255, 255);
    delay(100);
    CircuitPlayground.clearPixels();
  }
}

void sparkleRainbow()
{
  for(i=0; i<10; i++)
  {
    int rand = random(0, 10);
    int randColor1 = random(0, 256);
    int randColor2 = random(0, 256);
    int randColor3 = random(0, 256);
    CircuitPlayground.setPixelColor(rand, randColor1, randColor2, randColor3);
    delay(100);
    CircuitPlayground.clearPixels();
  }
}

void plusTwo()
{
  int rand = random(0, 10);
  int rand2 = random(0, 10);
  int randColor1 = random(0, 256);
  int randColor2 = random(0, 256);
  int randColor3 = random(0, 256);
  CircuitPlayground.setPixelColor(rand, randColor1, randColor2, randColor3);
  CircuitPlayground.setPixelColor(rand2, randColor3, randColor1, randColor2);

  delay(200);

  int ii = 9;
  
  for(int i = 0; i <= ii; i++)
  {
    if(i != rand && i != rand2)
    {
      CircuitPlayground.setPixelColor(i, randColor1, randColor2, randColor3);
    }
    if(ii != rand && ii != rand2)
    {
      CircuitPlayground.setPixelColor(ii, randColor1, randColor2, randColor3);
       
    }
    ii--;
   
    delay(200);
  }
  CircuitPlayground.clearPixels();
}

void loadingCycle()
{
  for(i=0; i < 10; i++)
  {
    CircuitPlayground.setPixelColor(i, 0, 255, 0);

    if(i + 1 >= 9)
    {
      int ii = 0;
      CircuitPlayground.setPixelColor(ii, 0, 255, 0);
      CircuitPlayground.setPixelColor(ii + 1, 0, 255, 0);
    }
    else
    {
      CircuitPlayground.setPixelColor(i + 1, 0, 255, 0);
      CircuitPlayground.setPixelColor(i + 2, 0, 255, 0);
    }
    delay(100);
    CircuitPlayground.clearPixels();
  }
}

void button4Pressed()
{
  button4Flag = 1;
}

void button5Pressed()
{
  button5Flag = 1;
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