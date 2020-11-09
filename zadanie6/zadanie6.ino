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
	
	pinMode(13, INPUT_PULLUP);
	
	Serial.begin(9600);
	reset();
}

// zmienne globalne
volatile unsigned int mode = 0;
unsigned long lastON = 0; //czas ostatniego zapalonego swiatlo
unsigned long lastOFF = 0;
bool button_pressed = 0; //opoznienie zeby nie zbierac wielokrotnuch nacisnien przycisku

unsigned int ontime = 0;
unsigned int offtime = 0;
unsigned int light = 0;


void display2Numbers(int first, int second)
{
	for(int i=0;i<5;i++)
		{
			digitalWrite(i+3,first & (1<<i) ? HIGH : LOW);
		}
	for(int i=0;i<5;i++)
		{
			digitalWrite(i+8,second & (1<<i) ? HIGH : LOW);
		}
}
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

	if(digitalRead(A0)==LOW)
		{
			ontime++;
			delay(100);
		}
	if(digitalRead(A1)==LOW)
		{
			ontime--;
			delay(100);
		}
	if(digitalRead(A2)==LOW)
		{
			offtime++;
			delay(100);
		}
	if(digitalRead(A3)==LOW)
		{
			offtime--;
			delay(100);
		}
	if(ontime>31)
		ontime=0;
	if(offtime<0)
		ontime=31;
	if(ontime>31)
		ontime=0;
	if(offtime<0)
		ontime=31;
	display2Numbers(ontime,offtime);
}
void lightsensormode()
{
	light = analogRead(A4);
	
  for(int i=0;i<10;i++)
		digitalWrite(i+3,(light/i)>10 ? HIGH : LOW);
	Serial.println("aplikacja korzystajaca z fotorezystora");
}

void alarmmode()
{
	if(millis()-lastON>ontime*100)
		{
			for(int i = 3; i<13;i++)
				{
					digitalWrite(i, LOW);
				}
			lastOFF=millis();
			Serial.println("alarm");
		}
	if(millis()-lastOFF>offtime*100)
		{
			for(int i = 3; i<13;i++)
				{
					digitalWrite(i, HIGH);
				}
			lastON=millis();
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
			delay(100);
			button_pressed=0;
		}
	
// sekcja odczytu przycisków zmiany trybu pracy:
  if (digitalRead(13) == LOW)
		{
			Serial.println("przycisniety 13");
			mode++;
			reset();
			button_pressed=1;
		}
	if(digitalRead(A0) ==LOW || digitalRead(A1) ==LOW || digitalRead(A2) ==LOW || digitalRead(A3) ==LOW)
		{
			mode=1;
			button_pressed=1;
		}
// sekcja wykonawcza, której przebieg zależy od bieżącego trybu pracy:
  switch (mode%6)
		{
		case 0:
			lightsensormode();
			break;
		case 1:
			settings();
			break;
		case 2:
			alarmmode();
			break;
		case 3:
			alarmmode();
			break;
		case 4:
			alarmmode();
			break;
	}
}
