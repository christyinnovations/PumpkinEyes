/*
  This method lowers and raises right pupil only
*/
void lazyEye()
{
  moveEyes(0, 1, 50);
  delay(500);
  
  // lower left pupil slowly
  for (int i=0; i<3; i++)
  {
    setRow(1, i+2, eyeBall[i+2]);
    setRow(1, i+3, eyeBall[i+3] & eyePupil);
    setRow(1, i+4, eyeBall[i+4] & eyePupil);
    delay(150);
  }
  
  delay(1000);
  
  // raise left pupil quickly
  for (int i=0; i<3; i++)
  {
    setRow(1, 4-i, eyeBall[4-i] & eyePupil);
    setRow(1, 5-i, eyeBall[5-i] & eyePupil);
    setRow(1, 6-i, eyeBall[6-i]);
    delay(25);
  }  
}
