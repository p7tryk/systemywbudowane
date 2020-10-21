#define LEDPIN 5

void setup()
{
	for(int i=3;i<14;i++)
		pinMode(i, OUTPUT);

	// ustawienie analogowego wejścia A3 jako wejście cyfrowe:
  pinMode(A0, INPUT);
	// włączenie na nim rezystora pull-up:
  digitalWrite(A0, HIGH);
	// ustawienie analogowego wejścia A3 jako wejście cyfrowe:
  pinMode(A1, INPUT);
	// włączenie na nim rezystora pull-up:
  digitalWrite(A1, HIGH);
}

// zmienna globalna przechowująca tryb pracy
int mode = 0;

void mode4()
{
	for(int i = 13; i>2;i--)
		{
			digitalWrite(i, HIGH);
			delay(500);
		}
	for(int i = 13; i>2;i--)
		{
			digitalWrite(i, LOW);
			delay(500);
		}
}

void mode3()
{
	for(int i = 13; i>2;i--)
		{
			digitalWrite(i, HIGH);
			delay(500);
			digitalWrite(i, LOW);
		}
}

void mode2()
{
	for(int i = 3; i<13;i++)
		{
			digitalWrite(i, HIGH);
			delay(500);
			digitalWrite(i, LOW);
		}
	delay(500);
}

void mode1()
{
	digitalWrite(LEDPIN, HIGH);
	delay(500);
	digitalWrite(LEDPIN, LOW);
	delay(500);
}

void mode0()
{
	for(int i = 3; i<13;i++)
		digitalWrite(i, HIGH);

	delay(500);
	
	for(int i = 3; i<13;i++)
		digitalWrite(i, LOW);
	delay(500);
}

void loop()
{
// sekcja odczytu przycisków zmiany trybu pracy:
  if (digitalRead(A0) == LOW)
    mode--;
  else if (digitalRead(A1) == LOW)
		mode++;
	
// sekcja wykonawcza, której przebieg zależy od bieżącego trybu pracy:
  switch (abs(mode)%5)
  {
  case 0:
    mode0();
		break;
	case 1:
		mode1();
		break;
	case 2:
		mode2();
		break;
	case 3:
		mode3();
		break;
	case 4:
		mode4();
		break;
	}
}
