//We always have to include the LedControl library
#include "LedControl.h"
#include <LedControl.h>

/*
 Create LetControl object, define pin connections
 We have 2 MAX72XX for eyes.
 */
#define PIN_EYES_DIN 12
#define PIN_EYES_CS 11
#define PIN_EYES_CLK 10
LedControl lc = LedControl(PIN_EYES_DIN, PIN_EYES_CLK, PIN_EYES_CS, 2);

// rotation
bool rotateMatrix0 = false;  // rotate 0 matrix by 180 deg
bool rotateMatrix1 = false;  // rotate 1 matrix by 180 deg

// define eye ball without pupil  
byte eyeBall[8]={
  B00111100,
  B01111110,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100
 };

byte eyePupil = B11100111;

// stores current state of LEDs
byte eyeCurrent[8];
int currentX;
int currentY;
int cntLoop = 0;
int cntEffect = 0;

// min and max positions
#define MIN -2
#define MAX  2

// delays
#define DELAY_BLINK 40   // "duration" of blink, smaller number blinks faster, larger number blinks slower

// perform an effect every # of loop iterations, 0 to disable
#define EFFECT_ITERATION 4

/*
  Arduino setup
*/
void setup() 
{
  Serial.begin(9600);
 
  randomSeed(analogRead(0));  // pick a random number to decide where to start
 
   
  // MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.shutdown(0,false);
  lc.shutdown(1,false);

  // set the brightness to low
  lc.setIntensity(0,1);
  lc.setIntensity(1,1);

  // clear both modules
  lc.clearDisplay(0);
  lc.clearDisplay(1);
 
  // LED test
  // vertical line
  byte b = B10000000;
  for (int c=0; c<=7; c++)
  {
    for (int r=0; r<=7; r++)
    {
      setRow(0, r, b);
      setRow(1, r, b);
    }
    b = b >> 1;
    delay(50);
  }
  // full module
  b = B11111111;
  for (int r=0; r<=7; r++)
  {
    setRow(0, r, b);
    setRow(1, r, b);
  }
  delay(500);
  
   // clear both modules
   
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  delay(500);

  // random seed
  randomSeed(analogRead(0));
 
  // center eyes, crazy blink
  displayEyes(0, 0);
  dlay(2000);
  blinkEyes(true, false);
  blinkEyes(false, true);
  dlay(1000);

}


void loop() 
{ 

  // move to random position, wait random time
  moveEyes(random(MIN, MAX + 1), random(MIN, MAX + 1), 50);
  delay(random(5, 7) * 500);
  
  // blink time?
  if (random(0, 3) == 0)  //  pick a random number between 0 - 3 if it's 3 then blink   if you change 3 to 5 there will be fewer blinks
  {
    delay(500);
    blinkEyes();
    delay(500);
  }
  
  
  
  // effect time?
  if (EFFECT_ITERATION > 0)
  {
    cntLoop++;
    if (cntLoop == EFFECT_ITERATION)
    {
      cntLoop = 0;
      if (cntEffect > 6) cntEffect = 0;
       switch(cntEffect)
      {
        case 0: // cross eyes
          crossEyes();
          dlay(1000);
          break;
    
        case 1: // round spin
          roundSpin(2);
          dlay(1000);
          break;
        
        case 2: // crazy spin
          crazySpin(2);
          dlay(1000); 
          break;
        
        case 3: // meth eyes
          goofyEyes();
          dlay(1000);
          break;
                
        case 4: // lazy eye
          lazyEye();
          dlay(1000);
          break;
          
        case 5: // crazy blink
          blinkEyes(true, false);
          blinkEyes(false, true);
          dlay(1000);
          break;

        case 6: // glow
          glowEyes(3);
          dlay(1000);
          break;

        default: 
          break;
      }
      cntEffect++;
    }
  }
}

/*
  This method corrects provided coordinate value
*/
int getValidValue(int value)
{
  if (value > MAX)
    return MAX;
  else if (value < MIN)
    return MIN;
  else
    return value;
}

/*
  Reverse bits in byte
  http://www.nrtm.org/index.php/2013/07/25/reverse-bits-in-a-byte/
*/
byte bitswap (byte x)
{
  byte result;
 
    asm("mov __tmp_reg__, %[in] \n\t"
      "lsl __tmp_reg__  \n\t"   /* shift out high bit to carry */
      "ror %[out] \n\t"  /* rotate carry __tmp_reg__to low bit (eventually) */
      "lsl __tmp_reg__  \n\t"   /* 2 */
      "ror %[out] \n\t"
      "lsl __tmp_reg__  \n\t"   /* 3 */
      "ror %[out] \n\t"
      "lsl __tmp_reg__  \n\t"   /* 4 */
      "ror %[out] \n\t"
 
      "lsl __tmp_reg__  \n\t"   /* 5 */
      "ror %[out] \n\t"
      "lsl __tmp_reg__  \n\t"   /* 6 */
      "ror %[out] \n\t"
      "lsl __tmp_reg__  \n\t"   /* 7 */
      "ror %[out] \n\t"
      "lsl __tmp_reg__  \n\t"   /* 8 */
      "ror %[out] \n\t"
      : [out] "=r" (result) : [in] "r" (x));
      return(result);
}


