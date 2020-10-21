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

changeMode(int change)
{
	mode+=change;
	if(mode<0)
		mode=0;
	if(mode>4)
		mode=4;
}

void loop() {
// sekcja odczytu przycisków zmiany trybu pracy:
  if (digitalRead(A0) == LOW)
    changeMode(-1);
  else if (digitalRead(A1) == LOW)
    changeMode(+1);
// sekcja wykonawcza, której przebieg zależy od bieżącego trybu pracy:
  switch (mode)
  {
  case 0:
		digitalWrite(LEDPIN, HIGH);
		delay(500);
		digitalWrite(LEDPIN, LOW);
		break;
  case 1:
    for(int i = 3; i<13;i++)
			digitalWrite(i, HIGH);
		delay(500);
		for(int i = 3; i<13;i++)
			digitalWrite(i, LOW);
		break;
	case 2:
		digitalWrite(LEDPIN+1, HIGH);
		delay(500);
		digitalWrite(LEDPIN+1, LOW);
		break;
	}
}
