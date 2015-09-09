/*
  This methods moves eyes to center position, 
  then moves horizontally with wrapping around edges.
*/
void crazySpin(int times)
{
  if (times == 0)
    return;
  
  moveEyes(0, 0, 50);
  delay(500);
  
  byte row = eyePupil;
  for (int t=0; t<times; t++)
  {
    // spin from center to L
    for (int i=0; i<5; i++)
    {
      row = row >> 1;
      row = row | B10000000;
      setRow(0, 3, row);  setRow(1, 3, row);  
      setRow(0, 4, row);  setRow(1, 4, row);
      delay(50); 
      if (t == 0) 
        delay((5-i)*10); // increase delay on 1st scroll (speed up effect)
    }
    // spin from R to center
    for (int i=0; i<5; i++)
    {
      row = row >> 1;
      if (i>=2) 
        row = row | B10000000;
      setRow(0, 3, row);  setRow(1, 3, row);  
      setRow(0, 4, row);  setRow(1, 4, row);
      delay(50);
      if (t == (times-1)) 
        delay((i+1)*10); // increase delay on last scroll (slow down effect)
    }
  }
}

