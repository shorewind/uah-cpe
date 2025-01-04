
void LogoPrint() {
  Serial1.print(x);
  Serial1.write(9);
  Serial1.print(y);
  Serial1.write(9);
  Serial1.print(U);
  Serial1.write(9);
  Serial1.print(theta*RadToDeg);  
  Serial1.println("  ");
}
