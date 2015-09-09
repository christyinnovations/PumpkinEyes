/*
  This method displays eyeball with pupil offset by X, Y values from center position.
  Valid X and Y range is [MIN,MAX]
  Both LED modules will show identical eyes
*/
void displayEyes(int offsetX, int offsetY) 
{
  // ensure offsets are  in valid ranges
  offsetX = getValidValue(offsetX);
  offsetY = getValidValue(offsetY);
  
  // calculate indexes for pupil rows (perform offset Y)
  int row1 = 3 - offsetY;
  int row2 = 4 - offsetY;

  // define pupil row
  byte pupilRow = eyePupil;

  // perform offset X
  // bit shift and fill in new bit with 1 
  if (offsetX > 0) {
    for (int i=1; i<=offsetX; i++)
    {
      pupilRow = pupilRow >> 1;
      pupilRow = pupilRow | B10000000;
    }
  }
  else if (offsetX < 0) {
    for (int i=-1; i>=offsetX; i--)
    {
      pupilRow = pupilRow << 1;
      pupilRow = pupilRow | B1;
    }
  }

  // pupil row cannot have 1s where eyeBall has 0s
  byte pupilRow1 = pupilRow & eyeBall[row1];
  byte pupilRow2 = pupilRow & eyeBall[row2];
  
  // display on LCD matrix, update to eyeCurrent
  for(int r=0; r<8; r++)
  {
    if (r == row1)
    {
      setRow(0, r, pupilRow1);
      setRow(1, r, pupilRow1);
      eyeCurrent[r] = pupilRow1;
    }
    else if (r == row2)
    {
      setRow(0, r, pupilRow2);
      setRow(1, r, pupilRow2);
      eyeCurrent[r] = pupilRow2;
    }
    else
    {
      setRow(0, r, eyeBall[r]);
      setRow(1, r, eyeBall[r]);
      eyeCurrent[r] = eyeBall[r];
    }
  }
  
  // update current X and Y
  currentX = offsetX;
  currentY = offsetY;
}

