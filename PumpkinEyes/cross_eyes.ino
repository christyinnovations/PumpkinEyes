/*
  This method crosses eyes
*/
void crossEyes()
{
  moveEyes(0, 0, 50);
  delay(500);

  byte pupilR = eyePupil;  
  byte pupilL = eyePupil;
  
  // move pupils together
  for (int i=0; i<2; i++)
  {
    pupilR = pupilR >> 1;
    pupilR = pupilR | B10000000;
    pupilL = pupilL << 1;
    pupilL = pupilL | B1;
    
    setRow(0, 3, pupilR); setRow(1, 3, pupilL);
    setRow(0, 4, pupilR); setRow(1, 4, pupilL);
    
    delay(100);
  }
  
  delay(2000);
  
  // move pupils back to center
  for (int i=0; i<2; i++)
  {
    pupilR = pupilR << 1;
    pupilR = pupilR | B1;
    pupilL = pupilL >> 1;
    pupilL = pupilL | B10000000;
    
    setRow(0, 3, pupilR); setRow(1, 3, pupilL);
    setRow(0, 4, pupilR); setRow(1, 4, pupilL);
    
    delay(100);
  }
}

