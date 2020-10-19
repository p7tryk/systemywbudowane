void setup()
{
  for (int i=3; i<13; ++i)
    pinMode(i, OUTPUT);
}

void loop()
{
  for (int i=3; i<13; ++i)
  {
    int j=i+3;
		int n=i+6;
    if(j>12)
      j-=10;
		if(n>12)
			n-=10;
    
    digitalWrite(i, HIGH);
    digitalWrite(j, HIGH);
		digitalWrite(n, HIGH);
    delay(500);
    digitalWrite(i, LOW);
    digitalWrite(j, LOW);
		digitalWrite(n, LOW);
  } 
}
