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
	// ustawienie analogowego wejścia A3 jako wejście cyfrowe:
  pinMode(A2, INPUT);
	// włączenie na nim rezystora pull-up:
  digitalWrite(A2, HIGH);
	// ustawienie analogowego wejścia A3 jako wejście cyfrowe:
  pinMode(A3, INPUT);
	// włączenie na nim rezystora pull-up:
  digitalWrite(A3, HIGH);
	
	Serial.begin(9600);
	reset();
}

// zmienne globalne
unsigned int mode = 0;
unsigned long lastON = 0; //czas ostatniego zapalonego swiatlo
bool button_pressed = 0; //opoznienie zeby nie zbierac wielokrotnuch nacisnien przycisku

unsigned int target = 0;
unsigned int test = 0;


void displayNumber(int number)
{
	int mask = 1;
	Serial.println(number);
	for(int i=0;i<10;i++)
		{
			digitalWrite(i+3,number & (1<<i) ? HIGH : LOW);
		}
}




void settings()
{

	if(digitalRead(A1)==LOW)
		{
			target++;
			delay(100);
		}
	if(digitalRead(A2)==LOW)
		{
			target--;
			delay(100);
		}
	displayNumber(target);
	test=0;
}

void alarmmode()
{
	if(millis()-lastON>1000)
		{
			for(int i = 3; i<13;i++)
				{
					if(digitalRead(i)==HIGH)
						{
							digitalWrite(i, LOW);
						}
					else
						{
							digitalWrite(i, HIGH);
						}
					lastON=millis();
				}
			Serial.println("alarm");
		}
}


void reset()
{
	for(int i=3;i<14;i++)
		{
			digitalWrite(i, LOW);
		}
	lastON = millis();
	Serial.println(mode);
	if(!mode)
		{
			Serial.println("alarm");	
		}
	else
		Serial.println("tryb ustawiania");
}

void loop()
{
	if(button_pressed==true)
		{
			delay(300);
			button_pressed=0;
		}
	
// sekcja odczytu przycisków zmiany trybu pracy:
  if (digitalRead(A0) == LOW)
		{
			mode=!mode;
			reset();
			button_pressed=1;
		}
	
	if (digitalRead(A1) == LOW)
		{
			test++;
			button_pressed=1;
		}
// sekcja wykonawcza, której przebieg zależy od bieżącego trybu pracy:
  switch (mode)
		{
		case 0:
			if(test>=target)
				alarmmode();
			else
				Serial.println(test);
			break;
		case 1:
			settings();
			break;
	}
}
