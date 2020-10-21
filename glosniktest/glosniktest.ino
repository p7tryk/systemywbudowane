void setup()
{

	for (int i=3; i<14; ++i)
    pinMode(i, OUTPUT);

	
	pinMode(A4, INPUT);
	digitalWrite(A4, HIGH);

	pinMode(2, OUTPUT);

}

void loop()
{
	if(digitalRead(A4) == LOW)
		{
			for (int i=3; i<14; ++i)
				digitalWrite(i, HIGH);
			delay(500);
			
		}
	for (int i=3; i<14; ++i)
    digitalWrite(i, LOW);

}
