USvoid setup()
{
  for (int i=3; i<13; ++i)
    pinMode(i, OUTPUT);
}

void loop()
{
  for (int i=3; i<13; ++i)
  {
    int j=i+5;
    if(j>12)
      j-=10;
    
    digitalWrite(i, HIGH);
    digitalWrite(j, HIGH);
    delay(500);
    digitalWrite(i, LOW);
    digitalWrite(j, LOW);
  } 
}
