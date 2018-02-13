/*
  Edited for 8x7 charlieplexing shield by Emily Hammes on 13/Feb/18
  
  Requires Charlieplexing8x7 library to run 
  This library is at hammeshacks.com 
  it is installed by downloading the .ccp and .h file, putting them in a zip file
  and then going to sketch -> include library in the arduino ide

  
  Original version of the code below was an example for the LOL shield written by
  Alex Wenger <a.wenger@gmx.de> http://arduinobuch.wordpress.com/
  at 26C3/Berlin on 30/Dec/09

*/
#include "Charliplexing8x7.h"

uint8_t heart_flag;

// column,row starting at (0,0)
uint8_t heart_p[] = {
  3,2,
  2,1,
  1,1,
  4,1,
  5,1,
  6,2,
  0,2,
  6,3,
  0,3,
  5,4,
  1,4,
  4,5,
  2,5,
  3,6,
};

struct point {
  uint8_t xp;        // Point Position in X direction (multplied by 16)
  uint8_t x_speed;   // Speed
  uint8_t flag;  
} points[9];

void setup()                    // run once, when the sketch starts
{
  LedSign::Init();
  
  for(uint8_t i = 0; i < 7; i++)
  {
    points[i].xp = 0;
    points[i].x_speed = random(1, 16);
    points[i].flag = 1;
  }
}


void heart()
{
  for(uint8_t y = 0; y < 7; y++)//rows
    for(uint8_t x = 0; x < 8; x++)//columns
    {
      LedSign::Set(x,y,0); //turn off all LEDS
    }
  for(uint8_t i = 0; i < 14; i++)
  {
    LedSign::Set(heart_p[i*2+1],heart_p[i*2],1); //turn on all 13 heart LEDS
  }
}


void loop()                     // run over and over again
{
  for(uint8_t i = 0; i < 7; i++)
  {
    points[i].xp += points[i].x_speed;
    if (points[i].xp >= 14*16) 
    {
      points[i].x_speed = random(1, 16);
      points[i].xp = 0;
      points[i].flag ^= 1;
    }
    LedSign::Set(points[i].xp/16,i,points[i].flag);    
  }
  
  heart_flag++;
  if (heart_flag < 20) {
    heart();
  }
  
  delay(40);
}
