/*
  This method blinks both eyes
*/
void blinkEyes()
{
  blinkEyes(true, true);
}

/*
  This method blinks eyes as per provided params
*/
void blinkEyes(boolean blinkLeft, boolean blinkRight)
{
  // blink?
  if (!blinkLeft && !blinkRight)
    return; 
  
  // close eyelids
  for (int i=0; i<=3; i++)
  {
    if (blinkLeft)
    {
      lc.setRow(0, i, 0);
      lc.setRow(0, 7-i, 0);
    }
    if (blinkRight)
    {
      lc.setRow(1, i, 0);
      lc.setRow(1, 7-i, 0);
    }
    delay(DELAY_BLINK);
  }
  
  // open eyelids
  for (int i=3; i>=0; i--) 
  {
    if (blinkLeft)
    {
      lc.setRow(0, i, eyeCurrent[i]);
      lc.setRow(0, 7-i, eyeCurrent[7-i]);
    }
    if (blinkRight)
    {
      lc.setRow(1, i, eyeCurrent[i]);
      lc.setRow(1, 7-i, eyeCurrent[7-i]);
    }
    delay(DELAY_BLINK);
  }
}


