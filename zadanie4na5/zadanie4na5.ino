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

// zmienne globalne
int mode = 0;
unsigned long lastON = 0; //czas ostatniego zapalonego swiatlo
unsigned long lastOFF = 0;
int usedpin = 0; //wybrany pin;
bool button_pressed = 0; //opoznienie zeby nie zbierac wielokrotnuch nacisnien przycisku
bool workmode=1;

void mode5()
{
	int j = 16-usedpin;
	if(millis()-lastON>500)
		{
			if(workmode==1)
				{
					digitalWrite(usedpin,LOW);
					digitalWrite(j,LOW);
					usedpin--;
					lastON=millis();
				}
			else
				{
					digitalWrite(usedpin,HIGH);
					digitalWrite(j,HIGH);
					usedpin--;
					lastON=millis();
				}
		}
	if(usedpin<7)
		{
			usedpin=13;
			workmode=!workmode;
		}
}

void mode4()
{
	if(millis()-lastON>500)
		{
			if(digitalRead(usedpin) == HIGH)
				{
					digitalWrite(usedpin,LOW);
					usedpin++;
				}
			else
				{
					digitalWrite(usedpin,HIGH);
					lastON=millis();
				}
		}
	if(usedpin>12)
		usedpin=3;
}

void mode3()
{
	if(millis()-lastON>500)
		{
			if(digitalRead(usedpin) == HIGH)
				{
					digitalWrite(usedpin,LOW);
					usedpin--;
				}
			else
				{
					digitalWrite(usedpin,HIGH);
					lastON=millis();
				}
		}
	if(usedpin<3||usedpin>13)
		usedpin=13;
	
}



void mode2()
{
	if(millis()-lastON>500)
		{
			if(workmode==1)
				{
					digitalWrite(usedpin,LOW);
					usedpin--;
					lastON=millis();
				}
			else
				{
					digitalWrite(usedpin,HIGH);
					usedpin--;
					lastON=millis();
				}
		}
	if(usedpin<3||usedpin>13)
		{
			usedpin=13;
			workmode=!workmode;
		}
}

void mode1()
{
	if(millis()-lastON>500)
		{
			if(digitalRead(LEDPIN)==HIGH)
				{
					digitalWrite(LEDPIN,LOW);
				}
			else
				{
					digitalWrite(LEDPIN,HIGH);
				}
			lastON=millis();
		}

}

void mode0()
{
	if(millis()-lastON>500)
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
		}
}

void reset()
{
	for(int i=3;i<14;i++)
		{
			digitalWrite(i, LOW);
		}
	usedpin = 0;
	lastON = millis();
	lastOFF = millis();
	button_pressed = 1;
	workmode = 1;
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
			mode++;
			reset();
		}
  else if (digitalRead(A1) == LOW)
		{
			mode--;
			reset();
		}
// sekcja wykonawcza, której przebieg zależy od bieżącego trybu pracy:
  switch (abs(mode)%6)
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
		case 5:
			mode5();
			break;
	}
}
