/*
  This method sets values to matrix row
  Performs 180 rotation if needed
*/
void setRow(int addr, int row, byte rowValue)
{
  if (((addr == 0) && (rotateMatrix0)) || (addr == 1 && rotateMatrix1))
  {
    row = abs(row - 7);
    rowValue = bitswap(rowValue);
  }

  lc.setRow(addr, row, rowValue);
}
