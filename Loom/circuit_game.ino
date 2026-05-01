#include <Adafruit_CircuitPlayground.h>

volatile int switchFlag, button4Flag, button5Flag;  // ISRs for switch and buttons declared
bool leftButtonPressed, rightButtonPressed; // button states declared to be read in
int i, ii;
int note = 0; // int variables declared + initialized
int delayTime = 125; 
int randPixel = random(0, 10);  
int score = 0;
int highScore = 0;
int modeCounter = 1;
int count = 0;

int song[12][2] = { // song matrix
    {64, 100},  
    {60, 100},  
    {68, 100},  
    {60, 100},  
    {67, 100},  
    {60, 100},  
    {64, 100},
    {60, 100},
    {72, 200},
  };

void setup() {
  CircuitPlayground.begin(); 
  Serial.begin(9600); // begin serial communcation
  attachInterrupt(digitalPinToInterrupt(4), button4Pressed, RISING); // attatch interrupt functions called
  attachInterrupt(digitalPinToInterrupt(5), button5Pressed, RISING);
  attachInterrupt(digitalPinToInterrupt(7), switchFlipped, CHANGE);
}

void loop() {
  // read in states of buttons
  leftButtonPressed = CircuitPlayground.leftButton();
  rightButtonPressed = CircuitPlayground.rightButton();

  // if user pauses game
  if(switchFlag)
  {
    CircuitPlayground.clearPixels();
    score = 0; // reset score
    // change gamemode
    switch(modeCounter)
    {
      case 1: 
      delayTime = 125;
      ++count;
      if(count <= 1)
      {
      Serial.println("Choose gamemode: 1. Faster");
      }
      break;

      case 2: 
      delayTime = 25;
      ++count;
      if(count <= 1)
      {
      Serial.println("Choose gamemode: 2. Slower");
      }
      break;

      case 3:
      delayTime = 50;
      ++count;
      if(count <= 1)
      {
        Serial.println("Choose gamemode: 3. Song");
      }
      break;

      case 4: 
      delayTime = random(25, 200);   
      ++count;
      if(count <= 1)
      {
        Serial.println("Choose gamemode: 4. Random"); 
      }

      case 5:
      ++count;
      if(count <= 1)
      {
        Serial.print("Current high score: ");
        Serial.println(highScore);
      } 
      break;

      break;
    }

    // toggle gamemode up
    if(button5Flag)
    {
      modeCounter++;
      
      if(modeCounter > 5)
      {
        modeCounter = 1;
      }

      count = 0;
      button5Flag = 0;
    }

    // toggle gamemode down
    if(button4Flag)
    {
      modeCounter--;

      if(modeCounter < 1)
      {
        modeCounter = 5;
      }
      
      count = 0;
      button4Flag = 0;
    }
  }

  // resume game
  if(switchFlag == 0)
  {
    // set random pixel on
    CircuitPlayground.setPixelColor(randPixel, 0, 155, 0); 

    // cycle through and keep random pixel on
    for(i = 0; i < 10; i++)
    {
      CircuitPlayground.setPixelColor(i, 0, 155, 0);

      if(i + 1 >= 9)
      {
        int ii = 0;
        CircuitPlayground.setPixelColor(ii, 0, 155, 0);
        CircuitPlayground.setPixelColor(ii + 1, 0, 155, 0);
      }
      else
      {
        CircuitPlayground.setPixelColor(i + 1, 0, 155, 0);
        CircuitPlayground.setPixelColor(i + 2, 0, 155, 0);
      }

      // if user prsses a button
      if(leftButtonPressed || rightButtonPressed)
      {
        // if when user presses button, the lead pixel in the cycle = the random pixel
        if(i == randPixel)
        {
          // play tone and increment score
          if(modeCounter == 3)
          {
            CircuitPlayground.playTone(((440 / 32.0) * pow(2.0, ((song[note][0] - 9.0) / 12.0))), 100);
            note++;

            if(note > 12)
            {
              note = 0;
            }
          }

          else
          {
            CircuitPlayground.playTone(100, 80);
          }
    
          Serial.println(++score);

          if(score >= highScore)
          {
            highScore = score; // set new high score
          }

          // new random pixel
          randPixel = random(0, 10);

          // manipulates the delayTime for the next cycle depending on gamemode
          switch(modeCounter)
          {
            case 1: 
            delayTime = delayTime - 2;
            break;
            
            case 2: 
            delayTime = delayTime + 2;
            break;

            case 3:
            if(count == 2 || count == 4 ||count == 6)
            {
              delayTime = 150;
            }
            delayTime = delayTime;

            break;

            case 4:
            delayTime = random(25, 200);
            break;

            default:
            delayTime = delayTime - 2;
            break;

          }
          break;
        }
      }

      // how fast the cycle goes
      delay(delayTime);

      // do not turn off the random pixel
      for (int j = 0; j < 10; j++) 
      {
        if (j != randPixel) 
        {
          CircuitPlayground.setPixelColor(j, 0, 0, 0);
        }
      }
    }
  }
  
}

void switchFlipped()
{
  // switch ISR turns switchFlag to true
  if(switchFlag == 1)
  {
    switchFlag = 0;
  }
  else
  {
    switchFlag = 1;
  }
}

void button4Pressed()
{
  // button4Flag set true
  button4Flag = 1;
  delay(100);
}

void button5Pressed()
{
  // button5Flag set true
  button5Flag = 1;
  delay(100);
}
