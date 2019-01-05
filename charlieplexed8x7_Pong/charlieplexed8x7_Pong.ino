#include <Charliplexing8x7.h>
#include <avr/pgmspace.h>

//**************************************************************//
//  Name    : Pong for Arduino / Charlieplexing                 //
//  Author  : Benjamin Sonntag http://benjamin.sonntag.fr/      //
//  Modified: Matt Mets http://cibomahto.com                    //
//  Date    : 28 May 2010                                       //
//  Modified: Emily Hammes for use with the 8x7 shield          //
//  Date    : 30 Nov 2018                                       //
//  Notes   : Uses Charlieplexing library to light up           //
//          : an 8x7 charlieplexed grid                         //
//          : from HammesHacks hammeshacks.com                  //
//**************************************************************//


/* ---------------------------------------------------------------------------*/
/** The figures from 0 to 9 encoded in 7 lines of 5 bits :
*/
PROGMEM const byte figures[][5] = {
  {2,5,5,5,2}, //0
  {2,3,2,2,2}, //1
  {3,4,2,1,7}, //2
  {3,4,3,4,3}, //3
  {5,5,7,4,4}, //4
  {7,1,7,4,7}, //5
  {6,1,3,5,2}, //6
  {7,4,4,2,2}, //7
  {7,5,7,5,7}, //8
  {2,5,6,4,2}  //9
};


int8_t x, y, dx, dy;
int8_t sh1y, sh2y, s1, s2;


/* ---------------------------------------------------------------------------*/
/* Arduino setup func
*/
void setup() {
  LedSign::Init(DOUBLE_BUFFER);

  x = 3;
  y = 5;
  sh1y = 3;
  sh2y = 3;
  dx = 1;
  dy = 1;
  s1 = 0;
  s2 = 0;

  randomSeed(analogRead(0));
  drawscores();
  Serial.begin(9600);
}


/* ---------------------------------------------------------------------------*/
/* Arduino main loop
*/
void loop() {
  int8_t randommove;

  if (y == 6 || y == 0) {
    dy = -dy;
  }

  // The Ball shall bounce on the walls :
  if (x == 6 || x == 1) {
   // ball can go at an angle or streight
    dx = -dx;

    int hit = 1;
    // Collision detection
    if (x == 1) {
      // check the first ship (left side)
      if (sh1y != y && sh1y + 1 != y) {
        s2++;
        drawscores();
        checkscores();
        hit = 0;
      }
    } else {
      // check the second ship (right side)
      if (sh2y != y && sh2y + 1 != y) {
        s1++;
        drawscores();
        checkscores();
        hit = 0;
      }
    }

    if (!hit) {
      Serial.print("pos ");
      Serial.print(dy); Serial.print(' ');
      Serial.println(y);
    }

    if (hit) {
      Serial.print(dy);
      Serial.print(' ');
      int r = random(0, 100);
      if (dy == 0) {
        if (r < 80)
          dy = random(0,2) * 2 - 1;
      } else {
        if (r < 10)
          dy = -dy;
        else if (r < 10+30)
          dy = 0;
      }

      if (y == 6 && dy == 1 || y == 0 && dy == -1) {
        dy = -dy;
      }

      Serial.println(dy);
    }
  }
  


  // Clear the non-active screen
  LedSign::Clear();

  // Move the BALL :
  x = x + dx;
  y = y + dy;

  // Draw the ball :
  LedSign::Set(x, y, 1);

  // Draw the Ship
  LedSign::Set(0, sh1y, 1);
  LedSign::Set(0, sh1y + 1, 1);
  LedSign::Set(7, sh2y, 1);
  LedSign::Set(7, sh2y + 1, 1);

  // The ships moves when the ball go in their direction. They follow it magically ;) :
  /* This code is too smart, in fact he is perfekt :)
    if (dx<0) {
    if (sh1y>y) {
      sh1y--;
    }
    if (sh1y<y) {
      sh1y++;
    }
    }
    // let's code a dummy one
  */

  if (dx>0) {
    // the ball goes away from me, let's move randomly
    randommove=random(0,3);
    if (randommove==0) {
      sh1y--;
    }
    if (randommove==1) {
      sh1y++;
    }
  } else {
    if (sh1y>y && (random(0,12)<10 || x<3)) {
      sh1y--;
    }
    if (sh1y<y && (random(0,12)<10 || x<3)) {
      sh1y++;
    }
    if (random(0,8)==0) {
      if (sh1y>y) {
        sh1y++;
      }
      if (sh1y<y) {
        sh1y--;
      }      
    }
  }

  if (dx<0) {
    // the ball goes away from me, let's move randomly
    randommove=random(0,3);
    if (randommove==0) {
      sh2y--;
    }
    if (randommove==1) {
      sh2y++;
    }
  } else {
    if (sh2y>y && (random(0,12)<10 || x<3)) {
      sh2y--;
    }
    if (sh2y<y && (random(0,12)<10 || x<3)) {
      sh2y++;
    }
    if (random(0,8)==0) {
      if (sh2y>y) {
        sh2y++;
      }
      if (sh1y<y) {
        sh2y--;
      }      
    }
  }

// Human Player
// 1/4 of the variator is used. If we use it fully, it's too hard to play.
// To use it fully replace 36 by 146
//sh2y = analogRead(5) / 72;

// Sanity checks for the ships :
if (sh1y > 5) sh1y = 5;
if (sh2y > 5) sh2y = 5;
if (sh1y < 0) sh1y = 0;
if (sh2y < 0) sh2y = 0;

// swap the screens ;) (sometime we may need this double-buffer algorithm...
// of course, as of today it's a little bit overkill ...)

LedSign::Flip();

// Display the bitmap some times
delay(200);

// loop :)
}


/* ---------------------------------------------------------------------------*/
/** Check if a player won !
   If one of the players won, let's show a funny animation ;)
*/
void checkscores() {
  // TODO : DO the animation ;)
}


/* ---------------------------------------------------------------------------*/
/** Draw the scores in a lovely scrolling :)
   Use the current active screen brutally ...
*/
void drawscores() {
    int8_t i,j,ps1;
  
    for(ps1=0;ps1<6;ps1++) {
      LedSign::Clear();  // Clear the active screen
  
  //    LedSign::Set(6,4,1); // dash between the scores
  //    LedSign::Set(7,4,1);
  
      // Fill it with both scores :
      // Left score goes up>down
      for (i=ps1, j=4; i>=0 && j>=0; i--, j--) {
        byte f = pgm_read_byte_near(&figures[s1][j]);
        for (uint8_t k = 0; k < 4; k++, f>>=1)
          LedSign::Set(k, i, f & 1);
      }
      // Right score goes down>up
      for (i=6-ps1, j=0; i<=6 && j<=4; i++, j++) {
        byte f = pgm_read_byte_near(&figures[s2][j]);
        for (uint8_t k = 0; k < 3; k++, f>>=1)
          LedSign::Set(k+5, i, f & 1);
      }
  
      LedSign::Flip();
      delay(200);
    }
  
    delay(1500);
  
    LedSign::Clear(0);
  
    if (s1==9 || s2==9) {
      for(ps1=0;ps1<3;ps1++) {
        LedSign::Flip();
        delay(300);
  
        LedSign::Flip();
        delay(600);
  
      }
      delay(1500);
  
      s1=0; s2=0;
      drawscores();
    }
}
