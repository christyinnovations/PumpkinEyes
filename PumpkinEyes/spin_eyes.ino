/*
  This method spins pupils clockwise
*/
void roundSpin(int times)
{
  if (times == 0)
    return;
  
  moveEyes(2, 0, 50);
  delay(500);
  
  for (int i=0; i<times; i++)
  {
    displayEyes(2, -1); delay(40); if (i==0) delay(40);
    displayEyes(1, -2); delay(40); if (i==0) delay(30);
    displayEyes(0, -2); delay(40); if (i==0) delay(20);
    displayEyes(-1, -2); delay(40);if (i==0) delay(10);
    displayEyes(-2, -1); delay(40);
    displayEyes(-2, 0); delay(40);
    displayEyes(-2, 1); delay(40);if (i==(times-1)) delay(10);
    displayEyes(-1, 2); delay(40);if (i==(times-1)) delay(20);
    displayEyes(0, 2); delay(40); if (i==(times-1)) delay(30);
    displayEyes(1, 2); delay(40); if (i==(times-1)) delay(40);
    displayEyes(2, 1); delay(40); if (i==(times-1)) delay(50);
    displayEyes(2, 0); delay(40);
  }
}

