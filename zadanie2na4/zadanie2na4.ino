void setup() {
  for (int i=3; i<13; ++i)
    pinMode(i, OUTPUT);
}

void loop() {
  for (int i=3; i<13; ++i)
  {
    digitalWrite(i, HIGH);
    if(i!=12)
    {
      delay(500);
      digitalWrite(i, LOW);
    }
  } 
for (int i=13; i>=3; --i)
  {
    digitalWrite(i, HIGH);
    if(i!=13&&i!=3)
      delay(500);
    digitalWrite(i, LOW);
  } 
}
