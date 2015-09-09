/*
  This method moves both eyes from current position to new position
*/
void moveEyes(int newX, int newY, int stepDelay)
{
  // set current position as start position
  int startX = currentX;
  int startY = currentY;
  
  // fix invalid new X Y values
  newX = getValidValue(newX);
  newY = getValidValue(newY);
  
  // eval steps
  int stepsX = abs(currentX - newX);
  int stepsY = abs(currentY - newY);

  // need to change at least one position
  if ((stepsX == 0) && (stepsY == 0))
    return;
   
  // eval direction of movement, # of steps, change per X Y step, perform move
  int dirX = (newX >= currentX) ? 1 : -1;
  int dirY = (newY >= currentY) ? 1 : -1;
  int steps = (stepsX > stepsY) ? stepsX : stepsY;
  int intX, intY;
  float changeX = (float)stepsX / (float)steps;
  float changeY = (float)stepsY / (float)steps;
  for (int i=1; i<=steps; i++)
  {
    intX = startX + round(changeX * i * dirX);
    intY = startY + round(changeY * i * dirY);
    displayEyes(intX, intY);
    delay(stepDelay);
  }
}
